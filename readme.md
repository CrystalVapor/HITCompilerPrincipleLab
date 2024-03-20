# 哈尔滨工业大学-编译原理2024-实验

## 版权声明

本实验代码由哈尔滨工业大学（本部）相关专业学生编写，仅用于学习交流，未经允许不得用于商业用途。
**由使用此代码造成的课业危险由使用者自行承担！！编写者不负任何责任！！**

## 模块

- `src/CmmLexer.l` 词法分析器
- `src/CmmParser.y` 语法分析器
- `src/ErrorReporter.c` 错误报告器，使用散列表实现
- `src/Structure/SimpleArray.c` 用于管理树节点，以及为高级数据结构提供基础的的简易动态数组
- `src/Structure/SimpleHashTable.c` 用于管理符号表和错误报告的简易哈希表
- `src/TokenName.c` 用于从符号枚举值获取符号名
- `src/SymbolTable.c` 符号表相关实现 (WIP)
- `src/ParserNodes.c` 语法树节点，使用动态数组实现
- `src/SemanticNodes.c` 语义树节点相关实现 (WIP)
- `Lab1.c` 实验一主程序，包含了词法分析器和语法分析器的调用
- `Lab2.c` 实验二主程序，包含了语义分析器的调用 (WIP)

## 项目编译

从主目录下：

```bash
cd CmakeBuild
cmake Lab1
make all
```

如果未安装cmake，可以直接使用make命令进行编译

## 项目测试

项目在`CmakeBuild/test`目录下内置了对于实验一的数个测试用例，可以通过执行`CmakeBuild`目录下的`Lab1BatchTest.sh`脚本进行测试
测试结果输出至`CmakeBuild/test/output`目录下同名.pst文件中

也可以单独执行./Lab1 [filename]进行测试

## 项目测试环境

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
