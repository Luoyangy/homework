#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Book.h"          // borrowBook 的参数是 Book&，必须先认识 Book

// ============================================================
// Student 类：学生
// 【实验二 · 依赖关系】图书馆借阅管理系统
// 与 Book 是【依赖关系】(use-a)：借书函数的参数里出现 Book 对象
// ============================================================

const int MAX_BORROW = 5;   // 一个学生最多能借几本

class Student {
private:

    std::string name;                        // 姓名
    std::string studentId;                   // 学号
    std::vector<std::string> borrowedTitles; // 已借图书的书名（STL 容器，长度自动增长）

public:

    Student();                                                        // 默认构造
    Student(const std::string& name, const std::string& studentId);   // 重载构造

    // ---- 设置（修改）数据成员 ----
    void setName(const std::string& name);
    void setStudentId(const std::string& studentId);

    // ---- 获取（读取）数据成员：只读，末尾 const ----
    std::string getName() const;
    std::string getStudentId() const;
    int         getBorrowCount() const;      // 已借数量 = borrowedTitles.size()

    // 还能不能借（没借满就能借）
    bool canBorrow() const;

    // ★★ 实验二核心：借书 —— 依赖关系的体现 ★★
    // 参数是 Book&（引用，不是值传递）：因为借书要真的改掉书的状态，
    // 值传递只能改到一份复印件，外面那本书不会变。
    // 返回 true = 借成功，false = 借失败（失败原因函数内打印）
    bool borrowBook(Book& book);

    void showInfo() const;                   // 打印学生信息 + 已借书目
};

#endif
