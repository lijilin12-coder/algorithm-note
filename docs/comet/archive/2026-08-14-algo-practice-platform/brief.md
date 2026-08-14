# Outcome

为妹妹（大一新生，主力设备 MacBook，备用 Win11）打造一个蓝桥杯算法刷题本地平台，
替代 Online OJ 的本地验证与调试能力，并在第二期加入 AI 辅助分析功能。

# Scope

**第一期 MVP**
- 基于 stdin/stdout 比对的本地测试框架（输入文件 → 运行程序 → 比对期望输出）
- 构建系统支持 macOS（Clang/GCC via Homebrew）和 WSL/Linux（GCC）
- 一键初始化脚本，克隆仓库后单命令完成环境配置
- 题目按分类（知识点）组织，每道题目含题目描述、测试用例、解答代码

**第二期**
- AI Agent 自动 code review（规范、安全漏洞建议）
- 历史提交分析，识别知识薄弱点

# Non-goals

- 不接入任何在线 OJ 账号或自动同步题目
- 不提供在线多人协作功能

# Acceptance examples

- 给定一道题目目录（题目描述 + 若干组 input/expected 测试用例文件），运行统一测试命令后，
  工具自动编译 C++ 解答，对每组测试用例运行程序并比对实际输出与期望输出，逐用例报告
  PASS/FAIL（含用例编号和差异摘要）。
- 新克隆仓库后，妹妹在 macOS（Homebrew 环境）运行一键初始化脚本，无需手动逐条安装
  编译器等依赖，脚本执行成功后可直接运行示例题目测试并得到 PASS。
- 同一套一键初始化脚本/命令在 Win11 WSL + GCC 环境下也能正常完成初始化，并成功运行
  示例题目测试。
- 新增一道题目时，只需按约定目录结构放入题目描述、测试用例和 C++ 解答文件，无需修改
  测试框架代码即可被识别和运行。

# Constraints and invariants

- 仓库当前已有 C 语言代码（linked_list/linked_list.c），新平台不得破坏已有文件结构
- 开发者在 WSL + GCC 下开发；妹妹主力使用 macOS，备用 Win11
- 蓝桥杯官方支持语言：C、C++、Python、Java；MVP 仅支持 C++
- MVP 交互形式为纯 CLI，不含 Web UI 或编辑器插件
- 第二期 AI 功能通过云端 API 接入，具体供应商在第二期启动时另行确定

# Decisions

- Q1 支持语言：仅 C++（MVP 范围内不支持 C、Python、Java）
- Q2 交互形式：纯 CLI（跨 macOS / WSL 一致可用，无需额外前端）
- Q3 第二期 AI 接入方式：云端 API（而非本地模型），具体供应商留待第二期确定

# Open questions

（无未解决问题）

# Verification expectations

- 针对测试框架本身（比较逻辑、多用例聚合、失败用例定位）的单元测试
- 至少一道示例题目端到端跑通：编译 → 运行全部测试用例 → 输出汇总结果，作为验收演示
- 一键初始化脚本在 macOS 和 WSL 两种环境下手动或自动化验证均可成功完成
