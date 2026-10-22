# 环境配置与使用

## 最小依赖

C++17 编译器（GCC 或 Clang）、Python 3.10+、一个编辑器。没有第三方 Python 包，不需要 CMake、Docker、IDE 插件或联网才能做本地题。比赛使用哪个 C++ 标准另行核实，本仓库使用结构化绑定等 C++17 语法；若比赛只支持旧标准，可改用 pair.first/second 和显式类型。

Linux：安装发行版的 g++、python3、git。macOS：安装 Xcode Command Line Tools 后可用 clang++；`CXX=clang++ python3 scripts/lab.py check all`。Windows：安装带 GCC 的 MSYS2 UCRT64 工具链，或使用已配置 g++ 的 WSL；Python 使用官方 3.10+，确保编译器和 Python 位于 PATH。仅安装 VS Code 不会提供 C++ 编译器。

```bash
g++ --version
python3 --version
python3 scripts/lab.py check sum64
```

Windows PowerShell 示例：

```powershell
python scripts/lab.py start ranking
python scripts/lab.py check ranking --mine
```

## 单文件运行（不用 Python 也能学）

```bash
g++ -std=c++17 -O2 -Wall -Wextra projects/01-stl/ranking.cpp -o ranking
./ranking
```

输入：

```text
3
bob 90
ann 90
cat 100
```

期望：`cat 100`、`ann 90`、`bob 90`，各一行。Windows 编译时可用 `-o ranking.exe`，运行 `./ranking.exe`。每个示例都有自己的 main，**不要把所有 cpp 一次链接成一个程序**。

## 练习工具

```bash
python3 scripts/lab.py list --level 2
python3 scripts/lab.py start maze
python3 scripts/lab.py check maze --mine
python3 scripts/lab.py run maze --mine --input your-input.txt
python3 scripts/lab.py log maze --status hinted --minutes 70 --note "漏掉入队标记"
python3 scripts/lab.py progress
```

`your-input.txt` 由你按题面创建。run 没有 `--input` 时从标准输入读到 EOF；Linux/macOS 用 Ctrl+D，Windows 控制台通常用 Ctrl+Z 后回车。

状态语义：attempted 尝试未完成；hinted 用过提示或答案；solved 独立写出并通过自测；reviewed 间隔后闭卷重做。工具不因测试通过自动修改状态。所有日期按 UTC 记录；你可在 note 中补充本地日期。

`check` 按空白分词比较整数/字符串输出，当前主任务没有浮点特判；它不是通用 OJ。默认单用例本地超时 3 秒，没有内存限制沙箱。只运行你信任的本地程序。编译产物缓存在 build，修改源码或编译选项会重新编译；删除 build 可清空缓存。

UBSan 可选：`python3 scripts/lab.py check all --sanitize`。如果本地编译器不支持 sanitizer，使用普通模式。调试数组越界还可以自行用 `-D_GLIBCXX_DEBUG` 或 AddressSanitizer；这些是本地调试方式，不必提交到 OJ。

## 保存到 GitHub

当前交付是本地 Git 仓库，未创建远程仓库。你的代码和学习记录都可以提交：

```bash
git status
git add practice progress
git commit -m "practice: finish week 01"
```

想同步到自己的 GitHub 时，先在网页创建空仓库，再把下面 OWNER 替换成你的账号：

```bash
git remote add origin https://github.com/OWNER/lanqiao-cpp-b-journey.git
git push -u origin main
```

ZIP 下载包不含 `.git` 历史；若从 ZIP 开始，请先 `git init -b main`、`git add .`、`git commit -m "init training repository"`。首次提交前若 Git 提示身份未配置，请使用你自己的 user.name / user.email。
