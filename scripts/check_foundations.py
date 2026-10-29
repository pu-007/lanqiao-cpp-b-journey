#!/usr/bin/env python3
"""基础补充题的样例和边界检查，不依赖第三方 Python 库。"""
import os
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
cases = {
    '01_max': [('5\n-4 -8 -1 -9 -3\n', '-1'), ('1\n-42\n', '-42')],
    '02_count': [('6\n60 59 100 0 60 80\n', '4'), ('1\n59\n', '0')],
    '03_digit_sum': [('2026\n', '10'), ('0\n', '0')],
    '04_reverse': [('bridge\n', 'egdirb'), ('x\n', 'x')],
    '05_find': [('5 7\n2 7 4 7 1\n', '2'), ('3 5\n1 2 3\n', '-1')],
    '06_distinct': [('7\n3 1 3 2 1 1 5\n', '4'), ('4\n8 8 8 8\n', '1')],
    '07_prefix': [('5 3\n2 1 4 -2 3\n1 3\n2 5\n4 4\n', '7 6 -2'), ('1 1\n1000000000\n1 1\n', '1000000000')],
    '08_lower_bound': [('6 4\n1 2 4 4 7 9\n', '3'), ('3 8\n1 2 3\n', '-1')],
    '09_gcd': [('48 18\n', '6'), ('7 7\n', '7')],
    '10_prime': [('49\n', 'NO'), ('2\n', 'YES')],
    '11_subarray': [('4 3\n1 2 1 2\n', '3'), ('3 0\n0 0 0\n', '6')],
    '12_stairs': [('4\n', '5'), ('0\n', '1')],
}
with tempfile.TemporaryDirectory(prefix='foundation-check-') as tmp:
    for name, examples in cases.items():
        src = root / 'docs/foundations/worked-code' / (name + '.cpp')
        exe = Path(tmp) / (name + ('.exe' if os.name == 'nt' else ''))
        subprocess.run([os.environ.get('CXX', 'g++'), '-std=c++17', '-O2', '-Wall', '-Wextra',
                        '-Werror', str(src), '-o', str(exe)], check=True, timeout=90)
        for data, expected in examples:
            result = subprocess.run([str(exe)], input=data, capture_output=True,
                                    text=True, check=True, timeout=3)
            if result.stdout.split() != expected.split():
                raise AssertionError(f'{name}: input={data!r}, expected={expected!r}, got={result.stdout!r}')
        print(f'PASS {name}: {len(examples)} cases')
print(f'PASS {len(cases)} programs, {sum(map(len, cases.values()))} cases')
