# Outcome

妹妹切换调试题目时，不再需要手动同步修改 `.vscode/launch.json` 和
`.vscode/tasks.json` 两处硬编码路径，只需打开对应题目的 `solution.cpp` 并按 F5，
调试器即自动对应到该题目。

# Scope

- `.vscode/launch.json` 与 `.vscode/tasks.json` 中原本硬编码的题目路径
  （`problems/examples/a-plus-b`）替换为 VS Code 内置变量 `${fileDirname}`
  （当前激活编辑器文件所在目录），使编译输出、调试目标随当前打开的 `solution.cpp`
  自动切换
- 覆盖已有的 Linux/WSL（gdb）与 macOS（lldb）两组配置

# Non-goals

- 不改变 `scripts/debug.sh` 命令行调试脚本的行为（该脚本已通过显式命令行参数指定
  题目目录，不存在“需要手动同步路径”的问题）
- 不做测试用例编号的自动检测/自动生成脚本；切换测试用例编号（如从 `1.in` 换成
  `2.in`）仍需手动编辑 launch.json 中该用例编号字符串（沿用 local-debug-support
  已确认的决定）
- 不改变 `scripts/run_tests.sh` 现有批量测试行为

# Acceptance examples

- 妹妹打开题目 A（如 `problems/examples/a-plus-b`）的 `solution.cpp` 并按 F5，
  无需编辑任何配置文件，调试器正确编译并调试题目 A 的 `solution.cpp`（使用默认
  测试用例 1 作为 stdin）。
- 妹妹随后打开题目 B（如 `problems/examples/max-of-three`）的 `solution.cpp` 并
  按 F5，无需改动 `launch.json`/`tasks.json` 任何内容，调试器自动对应到题目 B，
  而不是继续调试题目 A。
- 如需调试同一题目的其他测试用例（如 `2.in`），仍通过手动编辑 `launch.json` 中的
  用例编号完成，不要求额外脚本。
- Linux/WSL（gdb）与 macOS（lldb）两组调试配置均使用 `${fileDirname}` 自动对应
  当前题目。
- `scripts/debug.sh` 与 `scripts/run_tests.sh` 的现有行为不受影响。

# Constraints and invariants

- 依赖 VS Code 变量 `${fileDirname}`：其取值为“当前激活编辑器标签页文件所在目
  录”；调试前需要保证 `solution.cpp` 是当前激活的编辑器标签页
- 若启动调试时激活的编辑器不是目标题目的 `solution.cpp`（例如停留在
  `README.md`），编译/调试会指向错误目录——这是已知限制，需在 `launch.json`/
  `tasks.json` 注释中提示
- 不破坏已归档的 local-debug-support 验收行为（命令行调试、批量测试回归）

# Decisions

- Q1 自动检测范围：只对 VS Code 图形化调试（launch.json + tasks.json）生效，
  `scripts/debug.sh` 保持显式传参，不做改动
- Q2 测试用例切换方式：保持不变，仍需手动编辑用例编号字符串，本 change 只解决
  “题目文件夹”这一层路径的自动化

# Open questions

（无未解决问题）

# Verification expectations

- 在 WSL 环境下，分别打开示例题目 a-plus-b 与新增题目 max-of-three 的
  `solution.cpp`，实际按 F5（或等效的 preLaunchTask 编译 + gdb 启动）验证调试
  目标随当前打开文件自动切换，且断点可正常命中
- 确认 `scripts/debug.sh` 与 `scripts/run_tests.sh` 现有行为未被改动（复用已有
  框架自测与回归测试）
- 代码/配置走查确认 macOS（lldb）配置同样使用 `${fileDirname}`（已知限制：无法
  在真实 macOS 环境实机验证）
