# 目标

让本地刷题平台的初始化（setup）、测试（run_tests）和 VS Code F5 图形化调试在原生 Windows 上通过 Git Bash 可用，复用现有 bash 脚本，不另写 PowerShell 版本。

# 范围

- `scripts/run_tests.sh`：Git Bash 下单题目与批量模式均可运行 C++ 与 Python 题目。
- `scripts/setup.sh`：识别 Git Bash 环境（`uname -s` 为 `MINGW*`/`MSYS*`/`CYGWIN*`），通过 winget 安装缺失的 MSYS2/MinGW-w64 g++（含 gdb）与 Python，并自动把 MinGW `bin` 目录持久加入 Windows 用户 PATH。
- `scripts/lib/problem_language.sh` 等共用逻辑：Windows 下 Python 解释器选择（`python3` 不可用时回退到 `python`）。
- `.vscode/launch.json`、`.vscode/tasks.json`：新增 Windows C++ gdb 调试配置；Python debugpy 调试任务在 Windows 上经 Git Bash 运行。
- 仓库行尾规则（`.gitattributes`），保证 Windows 检出的 `.sh` 仍为 LF。
- README 更新支持环境与 Windows 说明。

# 非目标

- `scripts/debug.sh` 命令行调试在 Windows 上的支持。
- PowerShell / cmd 原生脚本。
- MSVC（cl.exe）编译器支持；Scoop/Chocolatey 安装方式。
- 在本仓库 CI 中真实运行 Windows 环境。

# 验收示例

- A1: Git Bash（uname 为 MINGW64_NT-*）下执行 `scripts/run_tests.sh problems/examples/a-plus-b`，C++ 题目编译为 `.exe` 并逐用例输出 PASS，退出码 0。
- A2: Git Bash 下仅有 `python`（无 `python3`）时，Python 题目无需设置 `PYTHON_BIN` 即可运行并判定 PASS/FAIL；显式设置 `PYTHON_BIN` 时优先使用该值。
- A3: 程序输出为 CRLF 行尾、或 `.in/.ans` 以 CRLF 检出时，内容相同的用例判定为 PASS。
- A4: Git Bash 下批量模式 `scripts/run_tests.sh problems` 能递归发现并运行 C++ 与 Python 题目，失败题目的汇总与退出码行为和 Linux 一致。
- A5: Git Bash 下超时（`RUN_TIMEOUT_SECONDS`）机制生效；环境缺少 `timeout` 时不超时直接运行，不报错中断。
- A6: Git Bash 下执行 `scripts/setup.sh`：g++ 与 Python 已存在则只报告版本；缺失时通过 winget 安装 MSYS2/MinGW-w64 工具链与 Python，并提示重开终端 / VS Code；winget 不存在时报错说明手动安装方法；两项仍不可用时以非 0 退出。
- A12: Git Bash 下执行 `scripts/setup.sh`，只要 MinGW `bin` 目录（默认 `C:\msys64\ucrt64\bin`，随 `MSYS2_ROOT` 变化）存在且不在 Windows 用户 PATH 中，就把它追加到用户 PATH 末尾（持久生效，不改系统 PATH，不删除或重排已有条目）并提示重开终端 / VS Code；已在用户 PATH 中时不重复添加；写入失败时输出手动添加说明，不改变退出码判定。
- A7: 在 Windows 上用 VS Code 打开某题 `solution.cpp` 按 F5，选择 "Debug (Windows - gdb)" 配置：自动以调试符号编译为 `solution_debug.exe`，以 `tests/1.in` 作为 stdin 启动 gdb 调试。
- A8: 在 Windows 上打开某题 `solution.py` 按 F5，"Debug Python (current problem)" 的前置任务在 Git Bash 中启动 debugpy 监听并成功 attach。
- A9: Windows 检出（`core.autocrlf=true`）后 `scripts/*.sh`、`tests/*.sh` 保持 LF 行尾，Git Bash 可直接执行。
- A10: README 写明 Windows（Git Bash）为支持环境，包含前置依赖（Git for Windows、winget）与使用方式，并说明 debug.sh 暂不支持 Windows。
- A11: macOS 与 WSL/Linux 上现有行为不变：`tests/run_framework_tests.sh` 在 Linux 上全部通过。

# 约束与不变量

- macOS 与 WSL/Linux 上的现有行为、输出格式和退出码保持不变。
- 题目目录约定（solution.cpp / solution.py 二选一、tests/<编号>.in/.ans）保持不变。
- Windows 支持只依赖 Git for Windows 自带的 Git Bash 工具集（bash、coreutils、diff 等）。

# 决策

- D1: Windows 通过 Git Bash 运行现有 `.sh` 脚本并做兼容修补，不新增 PowerShell 脚本。理由：单一代码库维护成本最低。
- D2: 本次覆盖 run_tests（单题/批量）、setup、VS Code F5 调试；`debug.sh` 命令行调试不在范围内。
- D3: setup 在 Windows 上通过 winget 自动安装 MSYS2/MinGW-w64 g++（含 gdb）与 Python，与现有 g++ 编译参数保持一致。
- D4: setup 自动把 MinGW `bin` 目录追加到 Windows **用户** PATH（无需管理员权限、不改系统 PATH），不再只提示用户手动添加；追加到末尾以免遮蔽已有工具；重复执行幂等；以 setup.sh 内联调用 Windows 自带 PowerShell 实现，不新增 .ps1 脚本，与 D1 一致。理由：用户于 2026-09-24 要求自动化该步骤。

# 待解决问题

（无；用户已于 2026-09-24 确认目标、范围、D1–D3、A1–A11 与非目标，并知悉 Windows 行为以模拟与配置审查方式验证；随后于同日确认新增 D4、A12 及 A6 提示文案调整。）

# 验证预期

- `tests/run_framework_tests.sh` 在 Linux 上全部通过，并新增覆盖 CRLF、python 回退、无 timeout、Windows uname 分支的框架测试。
- `.vscode/*.json` 配置经审查符合 cpptools / debugpy 的 Windows 用法。
- 真实 Windows 环境的手动验证由用户在归档后自行完成。
