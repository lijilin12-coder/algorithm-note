---
generated_from_state_version: 7
---

# Verification

## Current result

- Result: **Passed**
- Assurance: **skill-coordinated**
- Goal cycle: 1
- Iteration: 1
- Verifier attempt: 1
- Completed: 2026-08-14T03:05:43.696Z
- Summary: launch.json 与 tasks.json 的题目路径全部改为 ${fileDirname}，实现切换调试题目无需手动改配置；已在 a-plus-b 与新增的 max-of-three 两个题目上实机验证编译、断点命中与 stdin 重定向均正确随当前打开文件自动切换，回归测试与命令行调试脚本无regression。独立 Verifier 代码/配置走查确认全部 5 项验收标准通过。

## Acceptance

| ID | Result | Source | Criterion | Reason |
| --- | --- | --- | --- | --- |
| A1 | passed | brief.md | 妹妹打开题目 A（如 `problems/examples/a-plus-b`）的 `solution.cpp` 并按 F5， 无需编辑任何配置文件，调试器正确编译并调试题目 A 的 `solution.cpp`（使用默认 测试用例 1 作为 stdin）。 | launch.json 的 program/args 与 tasks.json 的编译输出/输入均改用 ${fileDirname}，不含任何硬编码题目路径，机制与具体题目文件夹无关 |
| A2 | passed | brief.md | 妹妹随后打开题目 B（如 `problems/examples/max-of-three`）的 `solution.cpp` 并 按 F5，无需改动 `launch.json`/`tasks.json` 任何内容，调试器自动对应到题目 B， 而不是继续调试题目 A。 | launch.json/tasks.json 中无任何残留的硬编码题目路径，切换当前激活的 solution.cpp 即可让全部路径自动对应新题目；已在 a-plus-b 与 max-of-three 两个题目上实机验证编译+断点命中且互不影响 |
| A3 | passed | brief.md | 如需调试同一题目的其他测试用例（如 `2.in`），仍通过手动编辑 `launch.json` 中的 用例编号完成，不要求额外脚本。 | launch.json 的 args 中仍保留字面量 tests/1.in，需手动编辑以切换用例编号，未新增自动生成脚本，符合 Non-goals |
| A4 | passed | brief.md | Linux/WSL（gdb）与 macOS（lldb）两组调试配置均使用 `${fileDirname}` 自动对应 当前题目。 | Debug (Linux/WSL - gdb) 与 Debug (macOS - lldb) 两组配置的 program/args 均一致改用 ${fileDirname} |
| A5 | passed | brief.md | `scripts/debug.sh` 与 `scripts/run_tests.sh` 的现有行为不受影响。 | scripts/debug.sh 与 scripts/run_tests.sh 未被修改，仍使用显式路径参数；回归测试（示例题目 2/2 x2、框架自测）与 debug.sh 命令行调试均实机验证通过 |

## Checks

_No Runtime checks were recorded._

## Blockers

_None._

## Risks and skipped work

- 调试前必须保证目标题目的 solution.cpp 是当前激活的编辑器标签页，否则 ${fileDirname} 会指向错误目录；已在 launch.json/tasks.json 注释与 README 中提示
- macOS(lldb) 分支的 ${fileDirname} 配置未在真实 macOS 环境实机验证，仅代码/配置走查（与既有 local-debug-support 已知风险一致）

## Previous iterations

| Goal cycle | Iteration | Attempt | Outcome | Unresolved | Summary | Completed |
| ---: | ---: | ---: | --- | --- | --- | --- |
| 1 | 1 | 1 | pass | — | launch.json 与 tasks.json 的题目路径全部改为 ${fileDirname}，实现切换调试题目无需手动改配置；已在 a-plus-b 与新增的 max-of-three 两个题目上实机验证编译、断点命中与 stdin 重定向均正确随当前打开文件自动切换，回归测试与命令行调试脚本无regression。独立 Verifier 代码/配置走查确认全部 5 项验收标准通过。 | 2026-08-14T03:05:43.696Z |

## Conclusion

launch.json 与 tasks.json 的题目路径全部改为 ${fileDirname}，实现切换调试题目无需手动改配置；已在 a-plus-b 与新增的 max-of-three 两个题目上实机验证编译、断点命中与 stdin 重定向均正确随当前打开文件自动切换，回归测试与命令行调试脚本无regression。独立 Verifier 代码/配置走查确认全部 5 项验收标准通过。
