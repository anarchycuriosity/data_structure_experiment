# 踩坑经验汇总

本目录记录在日常开发中遇到的各类问题及其解决过程。每个问题对应一个独立文档，按时间顺序编号。

---

## 目录

| 编号 | 文档 | 关键词 | 摘要 |
|------|------|--------|------|
| 01 | [01-vscode-cross-platform-config](01-vscode-cross-platform-config.md) | VS Code, 跨平台, 工作区配置, GDB | VS Code 工作区配置文件（tasks/launch/settings）的平台兼容性修复：利用 `windows`/`linux` 属性覆盖机制消除硬编码的平台依赖 |
| 02 | [02-vscode-f5-debug-fix](02-vscode-f5-debug-fix.md) | VS Code, F5, cppdbg, miDebuggerPath, GDB | F5 编译运行失败的诊断与修复：cppdbg 扩展在 Windows 上需要显式指定 miDebuggerPath 才能找到 MinGW GDB |
| 03 | [03-vscode-build-and-format-fix](03-vscode-build-and-format-fix.md) | VS Code, Shell Task, g++ PATH, 格式化, Prettier | Shell Task 跨 Shell 调用的隐式依赖修复 + C++ 格式化器正确选型 |
| 04 | [04-segfault-debugging-rooted-graph](04-segfault-debugging-rooted-graph.md) | 段错误, GDB, 有根有向图, 入度, DFS | 段错误三源定理与定位方法论 + 硬编码常量陷阱 + dg6.grp 图数据分析 |

---

## 核心理念

> 配置文件中的平台差异不应该靠「改来改去」解决，而应该利用工具内置的平台感知机制。

遇到跨平台配置问题时，优先查阅该工具是否提供了类似 VS Code 的 `windows`/`linux`/`osx` 条件覆盖能力。这是官方支持的标准做法，远比维护多份配置副本或手动切换来得可靠。
