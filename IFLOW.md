# IFLOW.md - rat-trig-cpp 项目指南

## 项目概述

`rat-trig-cpp` 是一个现代 C++ 实现的有理三角学（Rational Trigonometry）库。该项目基于现代 CMake 实践构建，提供了一个简洁的、与平台无关的库，适用于单头文件库和任何规模的项目。库专注于使用有理数和运算，而非无理数和极限，旨在简化和澄清经典三角学的概念。

## 项目架构

- **include/rattrig/trigonom.hpp**: 主要的头文件，包含所有核心函数模板定义
- **source/greeter.cpp**: 库的源代码文件（目前为空）
- **test/source/test_trigonom.cpp**: 测试文件，使用 doctest 框架进行单元测试
- **standalone/source/main.cpp**: 独立可执行文件的主入口点
- **CMakeLists.txt**: 主 CMake 配置文件
- **cmake/specific.cmake**: 特定依赖项配置文件
- **all/CMakeLists.txt**: 用于构建所有子项目的组合配置

## 核心功能

`rattrig` 命名空间中包含以下主要函数模板：

- `archimedes`: 使用阿基米德公式计算三角形的四边形面积
- `cross`: 计算两个 2D 向量的叉积
- `dot`: 计算两个 2D 向量的点积
- `quad`: 计算 2D 向量的平方长度（quadrance）
- `spread`: 计算两个 2D 向量之间的 spread
- `triple_quad_formula`: 使用三重平方公式计算
- `spread_law`: 使用 spread 定律计算

## 构建和运行

### 构建独立目标

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/RatTrig --help
```

### 运行测试套件

```bash
cmake -S test -B build/test
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test
# 或直接运行可执行文件:
./build/test/RatTrigTests
```

### 一次性构建所有内容

```bash
cmake -S all -B build
cmake --build build
```

### 代码格式化

```bash
cmake -S test -B build/test
cmake --build build/test --target format  # 查看更改
cmake --build build/test --target fix-format  # 应用更改
```

## 依赖管理

项目使用 CPM.cmake 进行依赖管理:
- fmt: 版本 10.2.1，用于格式化
- Fractions: 版本 1.0.1，用于分数运算（来自 luk036/fractions-cpp）

## 开发约定

- 使用 C++17 标准
- 遵循现代 CMake 实践
- 代码格式化使用 clang-format 和 cmake-format
- 测试使用 doctest 框架
- 支持代码覆盖率分析
- 遵循头文件包含守卫（pragma once）

## 项目特点

- 现代 CMake 实践
- 干净的库与可执行代码分离
- 集成测试套件
- 使用 GitHub Actions 进行持续集成
- 代码覆盖率通过 codecov.io 实现
- 使用 Format.cmake 强制执行代码格式化
- 使用 CPM.cmake 进行可重现的依赖管理
- 通过 PackageProject.cmake 实现可安装目标
- 使用 Doxygen 自动文档化
- 支持 sanitizer 工具和静态分析器

## 使用说明

此项目作为 C++ 库的模板，可以轻松调整为其他项目。要使用此模板，请将其作为模板创建新仓库，替换所有 "RatTrig" 实例为项目名称，并根据需要调整源文件。