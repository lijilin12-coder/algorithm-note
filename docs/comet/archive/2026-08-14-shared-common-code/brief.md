# Outcome

题目解答（`solution.cpp`）可以引用仓库统一维护的常用数据结构/工具头文件（如链表、
树、图），无需在每个题目里重复实现，同时不破坏现有单文件题目的编译、测试与调试
流程。

# Scope

- 仓库根目录新增 `common/` 目录，存放仅头文件（`.h`）形式的共享代码（模板/inline
  实现，无需单独编译链接）。
- `scripts/run_tests.sh`（`run_one_problem` 编译步骤）、`scripts/debug.sh`、
  `.vscode/tasks.json` 的编译命令统一加入 `-I <仓库根>/common`，使 `solution.cpp`
  可以用 `#include "linked_list.h"`、`#include "tree.h"` 等方式直接引用，不受题目
  目录嵌套深度影响。
- 提供至少一个共享头文件示例（如 `common/linked_list.h`，可参考现有
  [linked_list/linked_list.c](../../../linked_list/linked_list.c) 中的实现改写为
  C++ 模板/inline 头文件形式），并新增一个引用该共享头文件的示例题目验证端到端流程。
- 更新 `problems/README.md` 与根 `README.md`，说明 `common/` 的用途、引用方式与新增
  共享头文件的约定。

# Non-goals

- 不引入 Make/CMake 等新构建系统（用户已在此前讨论中明确拒绝引入额外构建复杂度）。
- 不要求把 `common/` 下的代码编译为独立的静态库或目标文件；仅头文件方案足够，不
  涉及多源文件链接。
- 不迁移 `linked_list/linked_list.c` 本身（该文件是仓库早期笔记，保留原样）；只是
  参考其实现，在 `common/` 下新写一份适合共享给题目使用的 C++ 头文件版本。
- 不强制现有题目改造为使用共享代码；共享代码是可选引用，现有 `solution.cpp` 不受
  影响。

# Acceptance examples

- A1: 新建一个示例题目（如 `problems/examples/linked-list-basic`），其
  `solution.cpp` 中 `#include "linked_list.h"` 引用 `common/linked_list.h` 提供的
  链表结构完成解答，运行 `scripts/run_tests.sh problems/examples/linked-list-basic`
  能正确编译并通过全部测试用例。
- A2: 对现有不引用 `common/` 的题目（如 `problems/examples/a-plus-b`）运行
  `scripts/run_tests.sh problems/examples/a-plus-b`，行为与引入 `common/` 之前完全
  一致（编译成功、用例 PASS/FAIL 输出不变）。
- A3: 使用 `scripts/debug.sh problems/examples/linked-list-basic 1` 对引用了
  `common/` 头文件的题目进行命令行调试，编译（带调试符号）成功且能进入 gdb/lldb。
- A4: 打开 `problems/examples/linked-list-basic/solution.cpp` 作为激活标签页，按 F5
  通过 VS Code 图形化调试，能成功编译（`-I common` 生效）并进入断点调试。
- A5: 批量测试 `scripts/run_tests.sh problems/examples` 时，同时包含引用 `common/`
  与不引用 `common/` 的题目，全部正确编译并通过（验证批量模式与共享头文件无冲突）。

# Constraints and invariants

- 共享头文件必须是纯头文件（`.h`），使用模板或 `inline`/`constexpr` 等避免多重
  定义问题，不新增需要单独编译的 `.cpp` 实现文件。
- `-I common` 使用相对仓库根目录的绝对路径注入（如 `-I "$REPO_ROOT/common"`），
  不依赖当前工作目录，保证从任意目录调用脚本都能正确解析。
- 不改变现有单题目/批量模式的输出格式、退出码约定（沿用 `run_one_problem` 现有
  编译/测试/清理逻辑，只在编译命令上追加 `-I` 参数）。
- 不得破坏 `tests/run_framework_tests.sh` 现有的框架自测。

# Decisions

- Q1: 共享代码存放目录 — 用户选择仓库根目录新建 `common/`（而非 `problems/common/`
  或其他自定义目录）。
- Q2: 引用方式 — 用户选择统一编译加 `-I common` 参数，`solution.cpp` 用
  `#include "文件名.h"` 直接引用（不用相对路径 `#include "../../../common/xxx.h"`），
  以便未来任意新增 `tree.h`、`graph.h` 等头文件都能用同样方式引用，不受题目嵌套
  深度影响。
- Q3: 共享代码形式 — 用户选择仅头文件（模板/inline 实现），不采用"头文件+.cpp
  实现需多文件编译链接"的方案，避免 `run_tests.sh`/`debug.sh`/`tasks.json` 的编译
  命令复杂化。

# Open questions

（无）

# Verification expectations

- 实机运行 A1-A5 五项验收标准对应的命令，确认编译、测试、调试均按预期工作。
- 确认现有题目（如 `a-plus-b`、`max-of-three`）不受影响，行为与引入 `common/`
  之前完全一致。
- 运行 `tests/run_framework_tests.sh` 确认无回归。
- 检查 `.vscode/tasks.json` 与 `scripts/debug.sh` 的编译命令均正确加入 `-I common`
  且路径基于仓库根目录，不依赖调用时的当前工作目录。
