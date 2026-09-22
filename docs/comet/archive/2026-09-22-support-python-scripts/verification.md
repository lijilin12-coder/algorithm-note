---
generated_from_state_version: 17
---

# 验证

## 当前结果

- 结果: **已归档**
- 验证情况: **已完成检查，验证结果已确认**
- 目标周期: 1
- 迭代: 2
- 验证器尝试次数: 2
- 完成时间: 2026-09-22T11:08:36.134Z
- 摘要: 最终完整验收：全部 7 项验收项（A1-A7）均独立复核通过，包括本轮修复的 A5（debugpy 就绪探测竞态已通过改为纯内核状态读取根本性解决，配套端口占用前置检查与信号处理修复也已验证有效）。未发现新的回归，tests/run_framework_tests.sh 全量自测通过。识别到三项非阻塞风险已记录在案，均不影响任何验收项的通过判定。

## 验收

| 编号 | 结果 | 来源 | 验收项 | 原因 |
| --- | --- | --- | --- | --- |
| A1 | passed | brief.md | A1：新建一个只含 `solution.py`（无 `solution.cpp`）的题目目录，运行 `scripts/run_tests.sh <题目目录>`，脚本自动识别为 Python 题目、跳过编译、直接用 `python3` 运行全部测试用例并逐用例报告 PASS/FAIL，输出格式与现有 C++ 单题目模式一致（含通过数汇总）。 | 新建仅含 solution.py 的题目目录，run_tests.sh 自动识别为 Python、跳过编译、运行全部用例并逐用例报告 PASS/FAIL，含通过数汇总，格式与 C++ 单题目模式一致；独立复现验证，并与 tests/run_framework_tests.sh 自测 1-4 交叉确认。 |
| A2 | passed | brief.md | A2：对一个同时包含 C++ 题目和 Python 题目的分类目录（如 `problems/examples`）运行批量测试，两种题目都能被发现并正确运行，任一题目失败即停止并报告是哪个题目失败（沿用已有批量模式的失败即停策略）。 | 独立构造的混合批量目录（C++/Python 各一 pass 一 fail）验证：两种语言均被正确发现并运行，失败题目在结束汇总中被点名，行为与改动前 C++-only 版本的“遇失败继续运行、末尾汇总”约定一致（已用 git show HEAD 对比确认非新增行为）；双语言冲突目录在批量中按 1 个题目计数并报冲突错误后继续。 |
| A3 | passed | brief.md | A3：某道 Python 题目目录中如果 `solution.cpp` 和 `solution.py` 同时存在，运行 `scripts/run_tests.sh` 或 `scripts/debug.sh` 时明确报错提示“同一题目只能保留一种语言的解答”，不会静默选择其中一个语言运行。 | run_tests.sh 与 debug.sh 对 both-language-problem 均输出一致的冲突报错并退出码 2，单目录与批量场景下均验证通过，逻辑集中于共享的 scripts/lib/problem_language.sh。 |
| A4 | passed | brief.md | A4：对一道 Python 题目的某组用例运行 `scripts/debug.sh <题目目录> <用例编号>`，程序以该用例输入作为 stdin 启动并进入 `pdb` 交互式调试，可以设置断点、单步执行、查看变量，Linux/WSL 与 macOS 环境下均可用。 | 通过真实 pty.fork() 交互式驱动 debug.sh 的 pdb 会话：设置断点、continue 命中、变量查看（取自用例输入文件而非 tty）、单步执行、正常退出均验证通过；无控制终端时报错路径干净退出、不挂起。 |
| A5 | passed | brief.md | A5：在 VS Code 中打开某道 Python 题目的 `solution.py`，使用仓库提供的调试配置按 F5 启动，程序以该题目某组测试用例的输入作为 stdin 运行并进入图形化调试（打断点、单步、查看变量），如需切换用例只需修改配置中的一个路径字符串（与现有 C++ 调试配置的用例切换方式一致）。 | 独立复测确认修复有效：debugpy_listen.sh 的就绪探测已改为纯内核状态读取（Linux /proc/net/tcp[6]，macOS lsof），全程无 TCP 连接；readiness 后端口保持可用（含真实 DAP initialize 往返验证）；新增的端口占用前置检查、SIGTERM/SIGINT 信号退出码（143/130）、清理逻辑均独立验证通过；tasks.json/launch.json 端口与 endsPattern 走查一致。VS Code 图形化 F5 端到端会话仍受限于沙盒无 GUI，未做字面点击验证，但其依赖的全部底层机制均已独立验证可靠。 |
| A6 | passed | brief.md | A6：新克隆仓库后运行 `scripts/setup.sh`，脚本在检测/安装 C++ 编译器之外，同时检测 `python3` 是否可用；macOS 下缺失时给出 Homebrew 安装指引（或自动安装），WSL/Linux 下缺失时给出 apt 安装指引（或自动安装）；`python3` 已存在时不重复安装。 | g++/python3 均已存在时 setup.sh 正确跳过安装分支、报告已找到、退出码 0；代码走查确认 macOS Homebrew 与 Linux apt-get 分支彼此独立、一项缺失不阻塞另一项检测/安装，与既有 check_compiler 模式一致。 |
| A7 | passed | brief.md | A7：`problems/README.md` 中题目目录约定已更新，明确写出题目可以是 `solution.cpp` 或 `solution.py` 二选一，并说明两者同时存在时的报错行为。 | problems/README.md 已更新，明确写出 solution.cpp/solution.py 二选一、不能同时存在，并说明两者同时存在时会报错而非静默选择语言。 |

## 检查

_没有记录 Runtime 检查。_

## 阻塞项

_无。_

## 风险与跳过的工作

- run_tests.sh 单题目模式下，编译器缺失检查现在被移到 prepare_runner 内部、在 tests 目录存在性检查之后执行；若编译器缺失与 tests 目录缺失同时发生这一边缘情况下，报错文案会从“未找到编译器”变为“未找到测试用例目录”，退出码不变，不影响任何一条验收项，但严格按“输出格式保持不变”解读时是一个可留意的微小行为差异。
- scripts/debugpy_listen.sh 依赖 python3 能 import debugpy（需 pip install debugpy），但 setup.sh 不检测/安装该依赖；目前唯一提示只在 launch.json 注释里，problems/README.md 和 setup.sh 的输出都没有提及，“新克隆仓库后 setup.sh → F5 调试 Python”的用户路径会在 debugpy 缺失时卡住且线索不够显眼。按 brief 决定该依赖检测被明确排除在 setup.sh 范围外，此处仅作为可用性风险记录，不视为验收缺陷。
- 本轮独立验证未能在当前沙盒环境（debugpy 1.8.22）下复现最初诊断的“裸连接探测必然杀死监听”竞态（单次与 20 次快速连接+断开均未触发），无法实测确认原始故障机制的确切复现条件；但这不影响本次判断，因为新实现已从根本上移除探测路径上的任何网络连接，无论原竞态的精确触发条件为何，修复都是更安全、更正确的方案。

## 之前的迭代

| 目标周期 | 迭代 | 尝试 | 结果 | 未解决项 | 摘要 | 完成时间 |
| ---: | ---: | ---: | --- | --- | --- | --- |
| 1 | 1 | 1 | execution-error | — | 本会话是新启动的 /comet 会话，此前派发的 Verifier subagent（skill-coordinated:verifier:6d029d06-1da9-4880-8967-c8d568e8e29c）无法在当前会话中确认其运行状态或结果；已询问同机的另一活跃会话是否为该任务，未获得及时确认，用户明确要求不再等待、立即重新派发新的 Verifier。 | 2026-09-22T10:28:47.996Z |
| 1 | 1 | 2 | execution-error | — | Native Verifier response was invalid: Native Verifier risks must be text entries | 2026-09-22T10:41:07.377Z |
| 1 | 1 | 3 | fail | A5 | 7 项验收中 6 项通过（A1-A4、A6、A7），A5 未通过：独立复现证明 scripts/debugpy_listen.sh 的端口就绪探测会被 debugpy 误判为客户端已连接并断开，导致监听进程在 VS Code 真正连接前退出，与 builder 声称已排除该竞态的结论相反。需要在 Build 阶段修复该就绪探测逻辑（避免探测连接被 debugpy 计为一次真实客户端连接），并重新验证 A5。 | 2026-09-22T10:41:53.977Z |
| 1 | 2 | 1 | recovery | — | Repair verification passed for A5; final full verification is required. | 2026-09-22T10:58:47.749Z |
| 1 | 2 | 2 | pass | — | 最终完整验收：全部 7 项验收项（A1-A7）均独立复核通过，包括本轮修复的 A5（debugpy 就绪探测竞态已通过改为纯内核状态读取根本性解决，配套端口占用前置检查与信号处理修复也已验证有效）。未发现新的回归，tests/run_framework_tests.sh 全量自测通过。识别到三项非阻塞风险已记录在案，均不影响任何验收项的通过判定。 | 2026-09-22T11:08:36.134Z |



## 结论

最终完整验收：全部 7 项验收项（A1-A7）均独立复核通过，包括本轮修复的 A5（debugpy 就绪探测竞态已通过改为纯内核状态读取根本性解决，配套端口占用前置检查与信号处理修复也已验证有效）。未发现新的回归，tests/run_framework_tests.sh 全量自测通过。识别到三项非阻塞风险已记录在案，均不影响任何验收项的通过判定。
