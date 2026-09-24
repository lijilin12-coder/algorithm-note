---
generated_from_state_version: 6
---

# 验证

## 当前结果

- 结果: **验收通过，需要你确认**
- 验证情况: **已完成检查，但需要你确认验证结果**
- 目标周期: 1
- 迭代: 1
- 验证器尝试次数: 1
- 完成时间: 2026-09-24T14:54:45.043Z
- 摘要: 在 Linux 上用伪造 uname、python3 存根、去掉 timeout 的 PATH、CRLF 用例、winget/MSYS2 存根和 autocrlf=true 克隆，逐项复现了 A1–A6、A9、A11，结果全部符合预期；A7、A8 按约定只做配置审查，未发现缺陷。主要剩余风险是没有真实 Windows 环境验证。

## 验收

| 编号 | 结果 | 来源 | 验收项 | 原因 |
| --- | --- | --- | --- | --- |
| A1 | passed | brief.md | A1: Git Bash（uname 为 MINGW64_NT-*）下执行 `scripts/run_tests.sh problems/examples/a-plus-b`，C++ 题目编译为 `.exe` 并逐用例输出 PASS，退出码 0。 | 用伪造 uname=MINGW64_NT-10.0-19045 并包装 g++ 模拟：C++ 题目以 -o <work>/solution.exe 编译，逐用例输出 PASS，退出码 0。 |
| A2 | passed | brief.md | A2: Git Bash 下仅有 `python`（无 `python3`）时，Python 题目无需设置 `PYTHON_BIN` 即可运行并判定 PASS/FAIL；显式设置 `PYTHON_BIN` 时优先使用该值。 | python3 为无法运行的应用商店占位存根、或 PATH 中没有 python3 时，都会自动回退到 python，并正确判定 PASS/FAIL；显式设置 PYTHON_BIN 时优先使用该值。 |
| A3 | passed | brief.md | A3: 程序输出为 CRLF 行尾、或 `.in/.ans` 以 CRLF 检出时，内容相同的用例判定为 PASS。 | C++ 程序输出 CRLF，配合 CRLF 的 .in/.ans：内容相同判 PASS、内容不同仍判 FAIL，FAIL 时打印去掉 CR 后的内容。实现先用 tr -d '\r' 去掉 CR，再做 diff -b -B。 |
| A4 | passed | brief.md | A4: Git Bash 下批量模式 `scripts/run_tests.sh problems` 能递归发现并运行 C++ 与 Python 题目，失败题目的汇总与退出码行为和 Linux 一致。 | Windows 模拟下批量运行（嵌套目录，C++ 与 Python 混合，含失败题目）：递归发现、失败后跳过继续、汇总文案和退出码 1 都与 Linux 下同一批次一致。 |
| A5 | passed | brief.md | A5: Git Bash 下超时（`RUN_TIMEOUT_SECONDS`）机制生效；环境缺少 `timeout` 时不超时直接运行，不报错中断。 | 有 timeout 时超时题目约 1s 被判为超时 FAIL；在 PATH 中剔除 timeout 并伪造 MINGW uname 后，不启用超时、直接运行并 PASS，没有报错中断。 |
| A6 | passed | brief.md | A6: Git Bash 下执行 `scripts/setup.sh`：g++ 与 Python 已存在则只报告版本；缺失时通过 winget 安装 MSYS2/MinGW-w64 工具链与 Python，并提示需要把 MinGW `bin` 目录加入 PATH / 重开终端；winget 不存在时报错说明手动安装方法；两项仍不可用时以非 0 退出。 | 用 winget、MSYS2 存根模拟四种场景：已存在时只报告版本、退出 0；缺失时通过 winget 安装并以 MSYSTEM=UCRT64 调用 pacman，同时提示设置 PATH 并重开终端；没有 winget 时报错并给出手动安装说明；仍不可用时退出码 1。 |
| A7 | passed | brief.md | A7: 在 Windows 上用 VS Code 打开某题 `solution.cpp` 按 F5，选择 "Debug (Windows - gdb)" 配置：自动以调试符号编译为 `solution_debug.exe`，以 `tests/1.in` 作为 stdin 启动 gdb 调试。 | 审查结论：cppdbg + gdb.exe，program 为 solution_debug.exe，args 用 < tests/1.in 重定向 stdin，preLaunchTask 在 windows 覆盖中以 -g -O0 编译出 .exe，路径用 strong 引用，JSON 解析正常，未发现具体缺陷。 |
| A8 | passed | brief.md | A8: 在 Windows 上打开某题 `solution.py` 按 F5，"Debug Python (current problem)" 的前置任务在 Git Bash 中启动 debugpy 监听并成功 attach。 | 审查结论：windows 覆盖用 Git Bash 的 bash.exe -c 执行 debugpy_listen.sh，路径用 strong 引用；脚本 Windows 分支用 netstat 按外部地址 :0 判断监听，与系统语言无关，已通过本地化 netstat 存根测试。 |
| A9 | passed | brief.md | A9: Windows 检出（`core.autocrlf=true`）后 `scripts/*.sh`、`tests/*.sh` 保持 LF 行尾，Git Bash 可直接执行。 | git check-attr 显示 *.sh、*.in、*.ans 均为 eol=lf；以 core.autocrlf=true 克隆的临时仓库中，.sh 与测试用例都没有 CR，而其他文本文件转成了 CRLF，说明检出规则生效。 |
| A10 | passed | brief.md | A10: README 写明 Windows（Git Bash）为支持环境，包含前置依赖（Git for Windows、winget）与使用方式，并说明 debug.sh 暂不支持 Windows。 | README 写明支持 Windows（Git Bash），列出 Git for Windows 与 winget 前置依赖、setup 步骤、PATH 设置和旧克隆的重新规范化方法，并说明 debug.sh 暂不支持 Windows、可改用 VS Code F5。 |
| A11 | passed | brief.md | A11: macOS 与 WSL/Linux 上现有行为不变：`tests/run_framework_tests.sh` 在 Linux 上全部通过。 | 在临时副本中重跑 tests/run_framework_tests.sh，自测 1–13 全部 OK、退出码 0；所有脚本 bash -n 通过；Linux 下原有行为未变。 |

## 检查

| 检查 | 命令 | 工作目录 | 状态 | 退出码 | 耗时 |
| --- | --- | --- | --- | ---: | ---: |
| 框架自测（含 Windows 模拟 7-13） | tests/run_framework_tests.sh | . | passed | 0 | 8367 ms |
| 脚本语法检查 | -c for f in scripts/*.sh scripts/lib/*.sh tests/*.sh; do bash -n "$f" \|\| exit 1; done | . | passed | 0 | 24 ms |

## 阻塞项

- **user**: The generic Skill bridge cannot prove an independent Verifier execution; user confirmation is required before Archive. — next: `await-user`

## 风险与跳过的工作

- 未在真实 Windows 上运行：MSYS 路径转换、timeout 能否 KILL 原生 exe、Git Bash 的 kill 能否终止原生 debugpy 进程，都只停留在推断，没有实测。
- A7：cpptools 在 Windows 上把 "<" 加反斜杠路径交给 gdb 重定向，对含空格的路径是否可靠尚未验证；gdb.exe 依赖 PATH 中有 MinGW bin。
- A8：Git Bash 路径写死为 C:\Program Files\Git\bin\bash.exe，装在其他位置需要手改（README 已说明）。
- CRLF 自测（自测 9）在旧脚本上也能通过（GNU diff -b 本来就忽略行尾 CR），区分力有限。
- 全新 MSYS2 上如需第二次 pacman -Syu，后续 -S 可能失败，需要用户重跑 setup。
- README 中的示例 problems/examples/a-plus-b 在仓库中不存在（本次变更之前就有的问题）。

## 之前的迭代

| 目标周期 | 迭代 | 尝试 | 结果 | 未解决项 | 摘要 | 完成时间 |
| ---: | ---: | ---: | --- | --- | --- | --- |
| 1 | 1 | 1 | pass | — | 在 Linux 上用伪造 uname、python3 存根、去掉 timeout 的 PATH、CRLF 用例、winget/MSYS2 存根和 autocrlf=true 克隆，逐项复现了 A1–A6、A9、A11，结果全部符合预期；A7、A8 按约定只做配置审查，未发现缺陷。主要剩余风险是没有真实 Windows 环境验证。 | 2026-09-24T14:54:45.043Z |



## 结论

在 Linux 上用伪造 uname、python3 存根、去掉 timeout 的 PATH、CRLF 用例、winget/MSYS2 存根和 autocrlf=true 克隆，逐项复现了 A1–A6、A9、A11，结果全部符合预期；A7、A8 按约定只做配置审查，未发现缺陷。主要剩余风险是没有真实 Windows 环境验证。
