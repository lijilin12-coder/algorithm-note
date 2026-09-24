# Capability: Windows（Git Bash）支持

## 概述

本地刷题平台在 macOS、WSL/Linux 之外，支持在原生 Windows 上通过 Git for Windows 自带的 Git Bash 运行现有 bash 脚本。不提供 PowerShell/cmd 原生脚本。Windows 支持范围：`scripts/setup.sh`、`scripts/run_tests.sh`（单题目与批量模式）、VS Code F5 图形化调试（C++ 与 Python）。`scripts/debug.sh` 命令行调试不支持 Windows。

## 平台识别

- `uname -s` 以 `MINGW`、`MSYS` 或 `CYGWIN` 开头时视为 Windows（Git Bash）环境。
- 其他平台（`Darwin`、`Linux`）的识别和行为不变。

## `scripts/run_tests.sh` 行为

- C++ 题目在 Windows 下编译产物带 `.exe` 后缀并可直接运行；编译命令与参数（`g++ -O2 -std=c++17 -Wall -I <common>`）不变，`CXX` 环境变量覆盖方式不变。
- Python 解释器选择：`PYTHON_BIN` 已设置时使用该值；未设置时使用 `python3`，`python3` 不可用（包括 Windows 应用商店占位别名无法实际运行的情况）时回退到 `python`。
- 输出比对忽略 CR 行尾差异：程序输出或 `.in/.ans` 文件为 CRLF 时，与 LF 内容等价判定。其余比对语义（`diff -b -B`）不变。
- 超时处理：`timeout` 命令可用时按 `RUN_TIMEOUT_SECONDS` 生效；不可用时不启用超时直接运行。
- 用例发现、PASS/FAIL 输出格式、批量模式递归发现、失败跳过与汇总、退出码与 Linux/macOS 一致。

## `scripts/setup.sh` 行为

- Windows（Git Bash）分支：
  - g++ / Python 已存在：跳过安装，报告版本（与其他平台一致）。
  - 缺失且 `winget` 可用：通过 winget 安装 MSYS2，并在 MSYS2 中安装 MinGW-w64 g++ 与 gdb 工具链；通过 winget 安装 Python。安装后提示用户把 MinGW `bin` 目录加入 PATH 并重新打开终端。
  - 缺失且 `winget` 不可用：报错，说明需要手动安装的软件和获取方式。
- 编译器与 Python 两项检测彼此独立；两项均可用才报告初始化完成，否则以非 0 退出。

## VS Code 集成

- `.vscode/launch.json` 新增 "Debug (Windows - gdb)" 配置：`cppdbg` + MinGW gdb，程序为 `${fileDirname}/solution_debug.exe`，以当前题目 `tests/1.in` 重定向 stdin，前置任务以调试符号编译当前题目。
- `.vscode/tasks.json` 的编译任务在 Windows 上输出 `solution_debug.exe`；Python debugpy 监听任务在 Windows 上通过 Git Bash 执行 `scripts/debugpy_listen.sh`，其他平台行为不变。
- 使用方式与其他平台一致：打开题目的 `solution.cpp` / `solution.py` 为当前标签页后按 F5。

## 仓库行尾

- `.gitattributes` 规定 `*.sh` 使用 LF 行尾，保证 Windows 检出（`core.autocrlf=true`）后脚本仍可在 Git Bash 中执行。

## 文档

- README 的“支持环境”包含 Windows（Git Bash），说明前置依赖（Git for Windows、winget）、首次初始化方式，以及 `debug.sh` 暂不支持 Windows（可用 VS Code F5 调试替代）。

## 明确不覆盖的行为

- `scripts/debug.sh` 在 Windows 上的命令行调试。
- PowerShell/cmd 原生脚本、MSVC 编译器、Scoop/Chocolatey 安装方式。
