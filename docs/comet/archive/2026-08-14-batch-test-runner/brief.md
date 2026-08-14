# Outcome

妹妹可以对某个分类目录（如 `problems/`、`problems/linked-list`）执行一条命令，
批量运行该目录下所有题目的测试用例，无需逐个题目手动调用。

# Scope

- 增强现有 `scripts/run_tests.sh`：传入的目录如果本身就是一个题目目录（直接包含
  `solution.cpp`），保持现有单题目行为不变；如果传入的目录不直接包含
  `solution.cpp`，则视为批量模式——递归扫描该目录下所有同时包含 `solution.cpp`
  和 `tests/` 的子目录（不限层级深度），按路径排序依次运行
- 批量模式下，任意一个题目编译失败或出现测试用例 FAIL，立即停止，不再运行后续题目
- 全部题目都通过时，输出批量汇总（已运行的题目数、总用例数等）

# Non-goals

- 不新增独立脚本，只增强现有 `scripts/run_tests.sh`
- 不支持在某个题目失败后继续运行并汇总所有题目结果（按用户决定：失败即停）
- 不改变单题目模式的现有输出格式和行为
- 不改变 `scripts/debug.sh` 与 VS Code 调试配置

# Acceptance examples

- 对一个题目目录（如 `problems/examples/a-plus-b`，直接包含 `solution.cpp`）运行
  `scripts/run_tests.sh problems/examples/a-plus-b`，行为与之前完全一致（单题目
  PASS/FAIL 输出）。
- 对一个包含多个题目的父目录（如 `problems/examples`，本身不含 `solution.cpp`）
  运行 `scripts/run_tests.sh problems/examples`，脚本自动识别为批量模式，依次编译
  并运行该目录下每个题目（如 a-plus-b、max-of-three）的全部测试用例，全部通过时
  输出汇总（如“共运行 N 个题目，全部通过”），退出码为 0。
- 对一个多层嵌套的父目录（如 `problems/linked-list`，其下含
  `problems/linked-list/single-linked-list` 等更深层的题目目录）运行批量测试，
  同样能递归发现并运行所有层级下的题目。
- 批量模式下，如果中途某个题目编译失败或出现用例 FAIL，脚本立即停止（不再运行后
  续题目），明确报告是哪个题目、哪一步失败，并以非 0 退出码退出。
- 对整个 `problems/` 目录运行批量测试，能递归发现全部题目并执行。

# Constraints and invariants

- 单题目模式的判定标准：目录直接包含 `solution.cpp` 即视为单题目目录
- 批量模式下题目发现顺序按路径字符串排序，保证结果可复现
- 复用现有单题目编译与比对逻辑（`g++ -O2 -std=c++17 -Wall`、`diff -b -B`），批量模
  式不重复实现比对逻辑
- 不破坏已归档 change 中 `tests/run_framework_tests.sh` 的自测预期

# Decisions

- Q1 实现方式：增强现有 `scripts/run_tests.sh`，不新增独立脚本
- Q2 批量模式失败处理：遇到第一个失败题目立即停止，不继续运行后续题目
- Q3 递归范围：支持任意层级嵌套（`problems/`、`problems/<分类>`、
  `problems/<分类>/<子分类>/...` 均可作为批量测试入口）

# Open questions

（无未解决问题）

# Verification expectations

- 单题目模式：对 `problems/examples/a-plus-b` 运行，确认行为与增强前一致（复用
  现有回归验证）
- 批量模式：对 `problems/examples`（含 a-plus-b、max-of-three 两个题目）运行，
  验证全部题目被发现并运行、全部通过时输出正确汇总、退出码为 0
- 批量模式失败路径：构造一个含 1 个正常题目 + 1 个故意失败题目的临时父目录，验证
  脚本在失败题目处停止、报告清晰、退出码非 0，且不运行失败题目之后的其他题目
  （若排序上还有更多题目）
- 多层嵌套：构造一个多层嵌套目录结构（模拟 `problems/linked-list/single-linked-list`），
  验证批量模式能递归发现并运行
- 回归：`tests/run_framework_tests.sh` 全部通过，确认框架自测不受影响
