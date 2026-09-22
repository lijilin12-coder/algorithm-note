# Capability: Python 语言支持

## 概述

本地刷题平台在已有 C++ 支持的基础上，为每道题目额外提供 Python 作为可选解答语言。一道题目在任意时刻只使用一种语言（`solution.cpp` 或 `solution.py`），测试、调试、初始化脚本对两种语言提供对等的操作方式。

## 题目目录约定（更新后完整版）

```
problems/<分类>/<题目名>/
  problem.md          # 题目描述
  solution.cpp         # C++ 解答，或
  solution.py           # Python 解答（二选一，不可同时存在）
  tests/
    1.in
    1.ans
    ...
```

- 一道题目目录中 `solution.cpp` 与 `solution.py` 只能存在一个。
- 语言判定完全基于文件是否存在，不依赖额外的配置文件或文件头标记。

## `scripts/run_tests.sh` 行为

- 判定顺序：给定题目目录后，检查 `solution.cpp` 与 `solution.py` 是否同时存在；若同时存在，报错退出（退出码 2），提示“同一题目只能保留一种语言的解答（solution.cpp 或 solution.py 二选一）”，并列出题目目录路径。
- 若只有 `solution.cpp`：沿用现有 C++ 流程（`g++ -O2 -std=c++17 -Wall -I <common>`，编译到临时目录后逐用例运行）。
- 若只有 `solution.py`：跳过编译步骤，直接使用 `python3 <solution.py>` 逐用例运行（解释器路径通过环境变量覆盖，默认 `python3`，行为对齐现有 `CXX` 环境变量模式）。
- 若两者都不存在：沿用现有报错（“未找到解答文件”），错误信息同时提及 `solution.cpp` 与 `solution.py` 均未找到。
- 用例发现、比对逻辑（`diff -b -B`）、超时处理（`RUN_TIMEOUT_SECONDS`）、PASS/FAIL 输出格式、批量模式的递归发现与失败即停策略，Python 题目与 C++ 题目完全一致，仅编译步骤不同。
- 批量模式下的题目发现逻辑扩展为：递归查找同时满足“存在 `tests/` 目录”且“存在 `solution.cpp` 或 `solution.py` 之一”的子目录（原实现只按 `solution.cpp` 查找）。

## `scripts/debug.sh` 行为

- 判定顺序与 `run_tests.sh` 一致：两者都存在报错退出；两者都不存在报错退出（提示信息同时提及两个候选文件名）。
- 若为 `solution.cpp`：沿用现有流程（按操作系统选择 gdb/lldb，先以调试符号编译）。
- 若为 `solution.py`：跳过编译步骤，执行 `python3 -m pdb <solution.py>`，并将指定用例的 `.in` 文件重定向为其 stdin（`python3 -m pdb solution.py < tests/<用例编号>.in`）。命令行调试对 Python 不区分操作系统，Linux/WSL 与 macOS 使用同一条命令。

## VS Code 集成

- `.vscode/tasks.json` 新增一个不执行编译、仅用于以 debugpy 监听模式启动 Python 目标的任务（作为 Python 调试配置的 `preLaunchTask`），负责把当前题目的默认用例输入（`tests/1.in`）重定向为被调试进程的 stdin。
- `.vscode/launch.json` 新增一个 Python 调试配置（示例名称：“Debug Python (current problem)”），使用 VS Code Python 扩展的 debugpy；效果对用户表现为：打开某题目的 `solution.py` 作为当前激活标签页后按 F5，即可对该题目以默认用例输入启动图形化调试。如需切换用例，与现有 C++ 配置一致：手动修改配置中指向用例输入文件的路径字符串。
- launch.json 中需要用注释写明：该配置依赖 VS Code 官方 Python 扩展（含 debugpy），以及为什么 Python 调试配置的内部实现方式（launch+attach）与 C++ 的 cppdbg 配置不同（不支持直接的 shell 风格 stdin 重定向参数），但最终对使用者仍是一次 F5。

## `scripts/setup.sh` 行为

- 在现有编译器检测逻辑基础上，新增对 `python3` 的检测：
  - 已存在：跳过安装，报告已找到的版本（沿用现有 `check_compiler` 风格的报告方式）。
  - macOS 缺失：通过 Homebrew 安装 Python（缺少 Homebrew 时报错提示先安装 Homebrew，与现有 g++ 分支一致）。
  - WSL/Linux 缺失：通过 `apt-get install -y python3` 安装（缺少 `apt-get` 时报错提示手动安装，与现有 g++ 分支一致）。
- 编译器与 Python 两项检测彼此独立：一项失败不阻止另一项继续检测/安装；脚本在两项都确认可用后才报告“环境初始化完成”，任一项最终仍不可用则报错退出。

## 文档

- `problems/README.md` 更新题目目录结构示例和文字说明，反映“`solution.cpp` 或 `solution.py` 二选一”的约定及两者共存时的报错行为。

## `.gitignore`

- 新增 `__pycache__/`、`*.pyc` 忽略规则，避免 Python 运行时产物被提交。

## 明确不覆盖的行为（非目标，见 brief）

- 不提供 Python 版共享数据结构库。
- 不支持单题目下 C++/Python 双语言并存运行。
- 不新增题目脚手架生成脚本。
