# 图书馆借阅管理系统

《面向对象程序设计（C++）》课程实验项目，使用 C++17 实现。

采用多文件组织（`.h` 声明 + `.cpp` 实现），围绕**组合关系（has-a）**
与**依赖关系（use-a）**两种类间关系进行设计。

## 功能

- 图书信息管理（名称、ISBN、出版社、价格、页数、在馆状态）
- ISBN 合法性校验（自行实现的 ISBN-13 校验位算法）
- 书架藏书管理（添加图书、显示全部藏书）
- 学生借书与借阅记录查询

## 类设计

| 类 | 关系 |
|---|---|
| `Book` | 独立类，封装图书属性 |
| `Bookshelf` | 与 `Book` 为**组合关系**（`Book books[10]` 作为数据成员） |
| `Student` | 与 `Book` 为**依赖关系**（`borrowBook(Book&)` 作为函数参数） |

## 编译运行

```bash
g++ -std=c++17 -Wall -g -o main.exe main.cpp Book.cpp Student.cpp Bookshelf.cpp
./main.exe
```
