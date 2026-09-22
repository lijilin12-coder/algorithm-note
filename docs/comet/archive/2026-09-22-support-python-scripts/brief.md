# 目标

在现有蓝桥杯刷题本地平台（目前仅支持 C++）基础上，让妹妹可以选择用 Python 编写某道题目的解答，并获得与 C++ 解答对等的本地测试、命令行调试和 VS Code 图形化调试体验，无需为 Python 题目额外学习一套不同的操作方式。

# 范围

- `scripts/run_tests.sh`：识别题目目录下的 `solution.py`（无 `solution.cpp` 时），跳过编译步骤，直接用 `python3` 运行每组测试用例、比对期望输出、报告 PASS/FAIL；批量模式下能在同一批次中混合发现并运行 C++ 与 Python 题目。
- `scripts/debug.sh`：识别到 `solution.py` 时，跳过编译步骤，改为对该文件启动 `python3 -m pdb`，并将指定用例输入重定向为其 stdin。
- `.vscode/launch.json` / `.vscode/tasks.json`：新增一套 Python 调试配置（使用 VS Code Python 扩展的 debugpy），效果对齐现有 C++ 的“打开 solution 文件 → F5 → 使用默认用例输入启动图形化调试”体验；如实现上需要 attach 而非 launch 才能重定向 stdin，需在配置注释中写清原理，但对使用者仍是单次 F5。
- `scripts/setup.sh`：新增检测 `python3` 是否可用的逻辑，缺失时按操作系统给出安装指引（macOS 走 Homebrew，WSL/Linux 走 apt），与现有 g++ 检测逻辑并列。
- `problems/README.md`：更新题目目录约定说明，解释题目可以选择 `solution.cpp` 或 `solution.py` 二选一，以及同时存在两个文件时的处理方式。
- `.gitignore`：补充 Python 运行产生的 `__pycache__/`、`*.pyc` 等忽略规则（此前只覆盖 C++ 编译产物）。

# 非目标

- 不为 Python 解答提供类似 `common/*.h` 的共享数据结构库（链表、树等）；Python 题目暂时各自独立实现，需要时另开需求。
- 不支持同一题目目录下 `solution.cpp` 与 `solution.py` 同时被识别并分别运行；两者同时存在时视为配置错误并明确报错，而不是静默选择其中一个。
- 不新增题目脚手架/模板生成脚本（当前 C++ 题目也是手动创建目录和文件，Python 沿用同样的手动方式）。
- 不改变现有 C++ 题目的行为、输出格式或调试配置。

# 验收示例

- A1：新建一个只含 `solution.py`（无 `solution.cpp`）的题目目录，运行 `scripts/run_tests.sh <题目目录>`，脚本自动识别为 Python 题目、跳过编译、直接用 `python3` 运行全部测试用例并逐用例报告 PASS/FAIL，输出格式与现有 C++ 单题目模式一致（含通过数汇总）。
- A2：对一个同时包含 C++ 题目和 Python 题目的分类目录（如 `problems/examples`）运行批量测试，两种题目都能被发现并正确运行，任一题目失败即停止并报告是哪个题目失败（沿用已有批量模式的失败即停策略）。
- A3：某道 Python 题目目录中如果 `solution.cpp` 和 `solution.py` 同时存在，运行 `scripts/run_tests.sh` 或 `scripts/debug.sh` 时明确报错提示“同一题目只能保留一种语言的解答”，不会静默选择其中一个语言运行。
- A4：对一道 Python 题目的某组用例运行 `scripts/debug.sh <题目目录> <用例编号>`，程序以该用例输入作为 stdin 启动并进入 `pdb` 交互式调试，可以设置断点、单步执行、查看变量，Linux/WSL 与 macOS 环境下均可用。
- A5：在 VS Code 中打开某道 Python 题目的 `solution.py`，使用仓库提供的调试配置按 F5 启动，程序以该题目某组测试用例的输入作为 stdin 运行并进入图形化调试（打断点、单步、查看变量），如需切换用例只需修改配置中的一个路径字符串（与现有 C++ 调试配置的用例切换方式一致）。
- A6：新克隆仓库后运行 `scripts/setup.sh`，脚本在检测/安装 C++ 编译器之外，同时检测 `python3` 是否可用；macOS 下缺失时给出 Homebrew 安装指引（或自动安装），WSL/Linux 下缺失时给出 apt 安装指引（或自动安装）；`python3` 已存在时不重复安装。
- A7：`problems/README.md` 中题目目录约定已更新，明确写出题目可以是 `solution.cpp` 或 `solution.py` 二选一，并说明两者同时存在时的报错行为。

# 约束与不变量

- 不破坏已归档能力：`scripts/run_tests.sh` 现有单题目/批量模式的 C++ 行为、输出格式、退出码保持不变；`scripts/debug.sh` 与现有 C++ VS Code 调试配置保持不变；`tests/run_framework_tests.sh` 现有自测继续通过。
- 题目目录约定沿用 `problems/README.md` 现有结构（`problem.md` + 解答文件 + `tests/<编号>.in`/`.ans`），只是解答文件允许是 `solution.py`。
- 比较逻辑复用现有实现（`diff -b -B`，忽略行尾空白和空行差异），不为 Python 题目单独实现一套比对逻辑。
- 蓝桥杯官方支持 C、C++、Python、Java；`docs/comet/archive/2026-08-14-algo-practice-platform` 中记录的 MVP 决策是“仅支持 C++”，本需求是在该决策基础上追加 Python 支持，不影响该 change 已归档的验收结论。
- 开发者在 WSL + GCC/Python 下开发验证；妹妹主力使用 macOS，备用 Win11（WSL）。
- Python 解释器统一使用 `python3`（与现有 `CXX` 环境变量模式一致，允许通过环境变量覆盖，默认值不变）。

# 决策

- Q1 题目语言与文件共存方式：一题一种语言，`solution.py` 与 `solution.cpp` 二选一；两者同时存在时报错，不做静默选择。
- Q2 调试支持范围：完整对等——同时提供 `scripts/debug.sh` 命令行 `pdb` 调试与 VS Code `launch.json` 图形化调试（debugpy）。
- Q3 共享代码库：本期不为 Python 提供 `common/` 等价模块，视为非目标。
- Q4 `scripts/setup.sh` 是否检测 Python：需要，保持一键初始化脚本对两种语言依赖的检测完整性。

# 待解决问题

（无未解决问题）

# 验证预期

- 针对 `scripts/run_tests.sh` 的 Python 单题目模式与批量模式（含 C++/Python 混合批量）分别验证 PASS 与 FAIL 场景，包括两个语言解答文件同时存在时的报错场景。
- 针对 `scripts/debug.sh` 的 Python 路径，验证 `pdb` 能正确以指定用例输入启动（可在 CI/无交互环境下验证进程能以给定 stdin 启动并接受基本 pdb 命令，而非要求人工交互）。
- VS Code 的 Python 调试配置通过配置走查确认（program/args/stdin 重定向或 attach 流程、problemMatcher 等字段），并在实际 VS Code 环境中手动验证一次 F5 调试可用。
- `scripts/setup.sh` 新增的 Python 检测逻辑在已装 `python3` 的环境下验证跳过安装、正常报告已找到；缺失场景通过代码走查确认安装分支正确（不强制在 CI 中真实卸载/安装 Python）。
- 回归：`tests/run_framework_tests.sh` 现有自测全部通过，确认框架自测不受影响。
