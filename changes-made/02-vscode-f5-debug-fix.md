# 问题 02：F5 无法一键编译运行 —— GDB 调试器路径缺失

## 问题现象

在完成 01 号问题的跨平台配置修复后，在 VS Code 中打开 `graph_test1.cpp`，按下 F5 时仍然无法成功编译运行。编译本身可以手动完成（终端中执行 `g++` 命令正常），但 F5 一键流程失败。

## 诊断过程

### 思维出发点

F5 在 VS Code 中的执行流程分为两个阶段：

```
F5 按下
  │
  ├─ (1) preLaunchTask: 执行 "Build Active File" 编译任务
  │     └─ 成功 → 进入阶段 (2)
  │     └─ 失败 → 报错终止
  │
  └─ (2) 启动调试器: cppdbg 尝试附加 GDB 到编译产物
        └─ 成功 → 程序启动，命中断点
        └─ 失败 → "无法启动调试" 错误
```

两个阶段中任何一个出问题，F5 都会失败。因此诊断必须**逐阶段排查**，不能笼统地认为「编译配置有问题」。

### 阶段 1 排查：编译任务是否正常

检查项：

| 检查项 | 方法 | 结果 |
|--------|------|------|
| g++ 是否在 PATH 中 | `which g++` | ✅ `/c/Program Files/mingw64/bin/g++` |
| 是否能手动编译成功 | 直接执行完整 g++ 命令 | ✅ 无错误输出 |
| 编译产物是否生成 | 检查 `bin/` 目录 | ✅ `graph_test1.exe` 生成 (203KB) |
| 编译产物是否能运行 | 执行 `./graph_test1.exe` | ✅ 正常输出 `9` |
| 头文件是否能找到 | `#include "..."` 在源文件同目录 | ✅ `src/graph/createGrpAdjMatrix.h` 存在 |
| `inc/` 目录是否存在 | `ls inc/` | ❌ 目录不存在（但 g++ 不报错，静默跳过） |

结论：**编译阶段没有问题**。手动执行和 F5 的 preLaunchTask 使用的是相同的 `g++` 命令和参数，编译理应成功。

### 阶段 2 排查：调试器启动是否正常

检查项：

| 检查项 | 方法 | 结果 |
|--------|------|------|
| C/C++ 扩展是否安装 | `code --list-extensions` | ✅ `ms-vscode.cpptools` v1.29.3 |
| GDB 是否在 PATH 中 | `which gdb` | ✅ `/c/Program Files/mingw64/bin/gdb` (GNU gdb 17.1) |
| launch.json 中 `miDebuggerPath` 是否设置 | 查看配置 | ❌ **未设置** |

### 根因定位

**`launch.json` 中缺少 `miDebuggerPath` 属性。**

VS Code 的 C/C++ 扩展（`cppdbg` 类型）在 Windows 上**不会自动搜索 PATH 中的所有目录来查找 GDB**。当 `miDebuggerPath` 未设置时，扩展使用默认值 `gdb`，但在 Windows 环境下它可能：

1. 尝试在当前工作目录查找 `gdb.exe` → 找不到
2. 尝试仅使用文件名 `gdb.exe` 通过 `CreateProcess` 启动 → 依赖系统 PATH，但 cpptools 内部处理逻辑不一定走系统 PATH

这在 Linux 上通常不是问题（`/usr/bin/gdb` 是标准路径），但在 Windows 上，MinGW 的安装路径各不相同（`C:\mingw64\bin\`、`C:\msys64\ucrt64\bin\` 等），扩展无法自动推断。

## 核心定理：cppdbg 的 miDebuggerPath 是强制性的跨平台属性

VS Code C/C++ 扩展文档中 `miDebuggerPath` 标记为"可选"，但实际上在 Windows + MinGW 组合下它**几乎是必须显式指定的**。原因：

- **Windows 没有标准的 GDB 安装位置**：不像 Linux `/usr/bin/gdb` 或 macOS 的 Xcode 工具链有固定位置
- **cpptools 的路径解析策略偏保守**：优先使用 `miDebuggerPath` 配置值，未设置时才回退到 `gdb` 字面量
- **MinGW 的 `gdb.exe` 可能不在 Windows 系统 PATH 中**：很多用户将 MinGW 路径添加到 Git Bash 的 PATH 而非 Windows 全局 PATH

## 解决方案

### `launch.json` 修复

在 `windows` 覆盖块中添加 `miDebuggerPath`，同时在 `linux` 块中也显式指定：

```json
"windows": {
    "program": "${workspaceFolder}/bin/${fileBasenameNoExtension}.exe",
    "miDebuggerPath": "C:/Program Files/mingw64/bin/gdb.exe"
},
"linux": {
    "miDebuggerPath": "/usr/bin/gdb"
}
```

注意：路径使用**正斜杠**（`/`），这是 MinGW GDB 可以接受的格式，且与 JSON 不冲突。

### 附加修复：创建缺失的 `inc/` 目录

`tasks.json` 中的编译参数包含 `-I ${workspaceFolder}/inc/`，但 `inc/` 目录在磁盘上不存在。虽然 g++ 静默跳过不存在的 `-I` 目录，但这是一个配置与文件系统不一致的问题，已通过创建 `inc/` 目录解决。

## 如果问题仍然存在

如果修复后仍然无法 F5 运行，按以下顺序排查：

1. **查看 VS Code 输出面板**：切换到 "输出" 标签，下拉选择 "C/C++" 查看扩展日志
2. **手动运行编译任务**：`Ctrl+Shift+B` → 选择 "Build Active File"，观察终端输出
3. **检查任务使用的 Shell**：确认 Git Bash 是否被正确用作任务 Shell
   ```json
   // 可在 settings.json 中显式指定（可选）
   "terminal.integrated.automationProfile.windows": {
       "path": "C:\\Program Files\\Git\\bin\\bash.exe"
   }
   ```
4. **杀进程重试**：残留的 gdb 进程可能占用端口，在任务管理器中结束 `gdb.exe` 后重试

## 关键感悟

1. **F5 是两步流程，排查必须分阶段**：编译和调试是两个独立环节，问题出在哪一级需要逐级验证，不能混为一谈。

2. **"可选"配置在跨平台场景下往往是"必填"**：`miDebuggerPath` 的文档描述是 optional，但那是针对「在标准路径安装了工具链」的假设。Windows 上没有「标准路径」这回事，所以 optional 变成了 required。

3. **平台差异不仅体现在文件后缀上**：01 号问题处理了 `.exe` 后缀的平台差异，但平台差异还包括工具链路径、Shell 行为、环境变量传递方式等更深层的问题。跨平台配置是一个持续完善的迭代过程。
