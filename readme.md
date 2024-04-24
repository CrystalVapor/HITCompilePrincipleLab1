# 哈尔滨工业大学-编译原理2024-实验

## 版权声明

本实验代码由哈尔滨工业大学（本部）相关专业学生编写，仅用于学习交流，未经允许不得用于商业用途。
**由不当使用此项目造成的课业危险由使用者自行承担！！编写者不负任何责任！！**

## 模块

- `src/CmmLexer.l` 词法分析器
- `src/CmmParser.y` 语法分析器
- `src/ErrorReporter.c` 错误报告器，使用散列表实现
- `src/SemanticAnalyzer.c` 语义分析器，在遍历语法树的基础上进行语义检查
- `src/InterCodeGenerator.c` 中间代码生成器，生成三地址码，手动实现了虚表和多态(只是为了好玩)
- `src/Structure/SimpleArray.c` 用于管理树节点，以及为高级数据结构提供基础的的简易动态数组
- `src/Structure/SimpleHashTable.c` 用于管理符号表和错误报告的简易哈希表
- `src/Structure/TokenName.c` 用于从符号枚举值获取符号名
- `src/Structure/SymbolTable.c` 符号表相关实现，支持了一套动态内存管理的符号表
- `src/Structure/ParserNodes.c` 语法树节点，使用动态数组实现
- `src/Structure/SemanticInfo.c` 语义信息，用于在语义节点中提供综合属性
- `Lab1.c` 实验一主程序，包含了词法分析器和语法分析器的调用
- `Lab2.c` 实验二主程序，包含了语义分析器的调用
- `Lab3.c` 实验三主程序，包含了中间代码生成器的调用

2024.4.8：项目全部模块编写完成，编写者不再主动更新，如发现问题请及时发issue反馈编写者以修正
*同样也欢迎发issue或邮件探讨项目的设计*

## 项目编译

首先切换到项目主目录（即CMakeLists.txt所在目录）
选定一个你喜欢的cmake构建目录名，此处以Cmake为例

```bash
mkdir Cmake
cd Cmake
cmake ..
```

cmake将创建所有所需make文件，如果你需要对项目进行debug，在cmake生成make文件时需要指定debug参数:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

在执行cmake指令后，你就可以在Cmake文件夹下使用make指令构建项目目标，使用指令

```bash
make all
```

以一次性构建Lab1-3的文件
你也可以指定性的构建Lab1-3中的任意一个，只需要将`all`替换成`Lab1`, `Lab2`, `Lab3`中的任意一个即可

项目的执行文件将生成在 `./crystal` 目录下。

## 项目测试

项目已在`./crystal`目录下提供测试脚本，可执行`LabXBatchTest.sh`测试实验X，相关样例在`testLabX`目录下

当执行脚本时:

实验一的树节点输出会被重定向到`testLab1/output/[caseName].pst`
报错信息将打印到屏幕中。

实验三的中间代码生成输出会被重定向到`testLab3/output/[caseName].ir`

也可以单独执行`./LabX [filename]`进行测试

## 项目测试环境

IDE: CLion 2023.3.4

*Thanks to JetBrains for providing the Education License!*

AI Assistant: GitHub Copilot

*Thanks to GitHub for providing the Education License!*

- Ubuntu 22.04.2 LTS
- gcc 11.4.0
- flex 2.6.4
- bison 3.8.2
- cmake 3.26.4
- make 4.3

*Required_min_version:*

- cmake 3.22
- flex 2.5.35
- bison 2.5.0
