# Outcome

在已完成的本地刷题 MVP 基础上，为妹妹提供方便的单用例调试能力，弥补 Online OJ
不提供调试功能的短板。

# Scope

- 针对某道题目的某一组测试用例，方便地启动调试（不只是跑批量测试看 PASS/FAIL）
- 覆盖 WSL/Linux（gdb）与 macOS（lldb）两种环境

# Non-goals

- 不实现图形化调试器 UI（依赖 VS Code 自带调试界面）
- 不改变现有 `scripts/run_tests.sh` 的批量测试行为

# Acceptance examples

- 妹妹对某道题目的某组测试用例执行统一调试命令后（如
  `scripts/debug.sh problems/examples/a-plus-b 1`），程序以该用例输入作为 stdin
  启动，并进入交互式调试器（WSL/Linux 下为 gdb，macOS 下为 lldb），可以设置断点、
  单步执行、查看变量。
- 妹妹在 VS Code 中打开某道题目的 `solution.cpp`，使用仓库提供的调试配置一键启动
  图形化调试（打断点、F5 运行、单步），默认使用该题目某组测试用例的输入作为程序
  输入；如需切换到其他用例，只需修改配置中的一个输入文件路径字符串。
- 该调试能力在 WSL/Linux（gdb）与 macOS（lldb）两种环境下均可使用。
- 新增调试能力不改变 `scripts/run_tests.sh` 现有的批量测试行为（仍然可以正常跑批
  量 PASS/FAIL）。

# Constraints and invariants

- 依赖已归档的 MVP（scripts/run_tests.sh、题目目录约定）不被破坏
- WSL 环境已确认有 gdb 可用；macOS 环境预期通过 lldb（Xcode Command Line Tools 自带）
- 调试功能同时提供命令行脚本（gdb/lldb）与 VS Code launch.json 两种入口
- VS Code 调试默认使用某题目的某组用例输入，通过手动编辑配置中的路径字符串切换用例，
  不引入额外的生成脚本

# Decisions

- Q1 调试形式：命令行脚本（gdb/lldb）+ VS Code launch.json 两者都提供
- Q2 VS Code 用例切换方式：launch.json 中用一个可直接编辑的路径字符串指向某组用例
  输入，用户手动修改以切换用例，不额外生成配置的脚本

# Open questions

（无未解决问题）

# Verification expectations

- 命令行调试脚本在 WSL 环境下针对示例题目实际启动 gdb 并验证 stdin 重定向正确
- VS Code launch.json 配置的正确性通过代码/配置走查确认（gdb 路径、program、args、
  stdin 重定向、macOS 对应的 lldb 配置字段）
- 确认 scripts/run_tests.sh 现有行为未被改动（复用已有框架自测）
