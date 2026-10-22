#!/usr/bin/env python3
"""零第三方依赖的训练工具。只编译本仓库或你指定的本地 C++ 文件。"""
import argparse
import csv
import datetime as dt
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
TASKS = json.loads((ROOT / 'tests/manifest.json').read_text(encoding='utf-8'))
BY_ID = {t['id']: t for t in TASKS}


def compile_source(source, sanitize=False):
    source = Path(source).resolve()
    compiler = os.environ.get('CXX', 'g++')
    if not shutil.which(compiler):
        raise RuntimeError(f'找不到编译器 {compiler}；请读 docs/setup.md 配置 CXX 或 PATH。')
    flags = ['-std=c++17', '-O2', '-Wall', '-Wextra', '-Wshadow', '-pedantic']
    if sanitize:
        flags = ['-std=c++17', '-O1', '-g', '-Wall', '-Wextra',
                 '-fsanitize=undefined', '-fno-sanitize-recover=all']
    # 缓存键包含源码、编译器路径/版本和编译选项，防止切换工具链后用旧程序。
    version = subprocess.run([compiler, '--version'], capture_output=True, check=True).stdout
    digest = hashlib.sha256(source.read_bytes() + repr(flags).encode()
                            + str(shutil.which(compiler)).encode() + version).hexdigest()[:20]
    folder = ROOT / 'build'
    folder.mkdir(exist_ok=True)
    target = folder / (digest + ('.exe' if os.name == 'nt' else ''))
    if not target.exists():
        result = subprocess.run([compiler, *flags, str(source), '-o', str(target)],
                                capture_output=True, text=True, timeout=90)
        if result.stderr:
            print(result.stderr, file=sys.stderr, end='')
        if result.returncode:
            raise RuntimeError(f'编译失败：{source.relative_to(ROOT) if source.is_relative_to(ROOT) else source}')
    return target


def execute(binary, data, timeout=3.0):
    try:
        result = subprocess.run([str(binary)], input=data, text=True, capture_output=True,
                                timeout=timeout, encoding='utf-8')
    except subprocess.TimeoutExpired as exc:
        raise RuntimeError(f'超过本地时间限制 {timeout}s（非官方时限）') from exc
    if result.returncode:
        raise RuntimeError(f'程序异常退出 {result.returncode}\n{result.stderr[:2000]}')
    return result.stdout


def check(task, source, sanitize=False):
    binary = compile_source(source, sanitize)
    for number, case in enumerate(task['cases'], 1):
        actual = execute(binary, case['input'])
        if actual.split() != case['output'].split():
            raise RuntimeError(f'{task["id"]} 用例 {number} 未通过\n输入：{case["input"]!r}'
                               f'\n期望：{case["output"]!r}\n实际：{actual!r}')
    print(f'PASS {task["id"]}: {len(task["cases"])} cases')


def main():
    parser = argparse.ArgumentParser(description='蓝桥 C++ B 阶梯训练工具')
    sub = parser.add_subparsers(dest='command', required=True)
    ls = sub.add_parser('list', help='列出任务'); ls.add_argument('--level', type=int)
    start = sub.add_parser('start', help='生成独立答题文件，不含参考算法')
    start.add_argument('id', choices=BY_ID)
    run = sub.add_parser('run', help='编译并运行；默认执行参考答案')
    run.add_argument('id', choices=BY_ID); run.add_argument('--mine', action='store_true')
    run.add_argument('--input', type=Path); run.add_argument('--sanitize', action='store_true')
    test = sub.add_parser('check', help='运行样例和固定边界用例')
    test.add_argument('id', choices=['all', *BY_ID]); test.add_argument('--mine', action='store_true')
    test.add_argument('--sanitize', action='store_true')
    log = sub.add_parser('log', help='追加本地训练记录，不自动宣称掌握')
    log.add_argument('id', choices=BY_ID)
    log.add_argument('--status', required=True, choices=['attempted', 'hinted', 'solved', 'reviewed'])
    log.add_argument('--minutes', type=int, required=True); log.add_argument('--note', default='')
    sub.add_parser('progress', help='显示最近一次状态和已投入时间')
    args = parser.parse_args()
    if args.command == 'list':
        for t in TASKS:
            if args.level is None or t['level'] == args.level:
                print(f'L{t["level"]} {t["id"]:23} {t["title"]}  [{t["project"]}]')
    elif args.command == 'start':
        t = BY_ID[args.id]; p = ROOT / 'practice' / f'{args.id}.cpp'
        if p.exists():
            print(f'已存在，保留你的代码：{p}'); return
        header = f'// 练习：{t["title"]}\n// 题面：{Path(t["path"]).with_suffix(".md")}\n'
        p.write_text(header + (ROOT/'templates/main.cpp').read_text(encoding='utf-8'), encoding='utf-8')
        print(f'已创建 {p}')
    elif args.command in ('run', 'check'):
        selected = TASKS if args.id == 'all' else [BY_ID[args.id]]
        for t in selected:
            source = ROOT / (f'practice/{t["id"]}.cpp' if args.mine else t['path'])
            if not source.exists():
                raise RuntimeError(f'未找到答题文件，请先执行 start {t["id"]}')
            if args.command == 'check':
                check(t, source, args.sanitize)
            else:
                data = args.input.read_text(encoding='utf-8') if args.input else sys.stdin.read()
                print(execute(compile_source(source, args.sanitize), data), end='')
    elif args.command == 'log':
        if args.minutes < 0:
            raise RuntimeError('训练分钟数不能为负。')
        path = ROOT/'progress/attempts.csv'
        exists = path.exists() and path.stat().st_size > 0
        now = dt.datetime.now(dt.timezone.utc).date()
        with path.open('a', encoding='utf-8', newline='') as f:
            writer = csv.writer(f)
            if not exists: writer.writerow(['date_utc', 'id', 'status', 'minutes', 'note', 'review_due'])
            writer.writerow([now.isoformat(), args.id, args.status, args.minutes, args.note,
                             (now+dt.timedelta(days=2)).isoformat()])
        print('已记录。建议 2 天、7 天、21 天后分别闭卷重做。')
    else:
        path = ROOT/'progress/attempts.csv'
        rows = list(csv.DictReader(path.open(encoding='utf-8'))) if path.exists() else []
        latest = {r['id']: r for r in rows}
        print(f'记录 {len(rows)} 次，累计 {sum(int(r["minutes"]) for r in rows)} 分钟')
        for t in TASKS:
            r = latest.get(t['id'])
            print(f'{t["id"]:23} {r["status"] if r else "todo"}')


if __name__ == '__main__':
    try:
        main()
    except (RuntimeError, OSError, subprocess.SubprocessError) as exc:
        print(f'ERROR: {exc}', file=sys.stderr)
        sys.exit(1)
