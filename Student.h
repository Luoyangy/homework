#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Book.h"          


const int MAX_BORROW = 5;   // 一个学生最多能借几本

class Student {
private:

    std::string name;                        // 姓名
    std::string studentId;                   // 学号
    std::vector<std::string> borrowedTitles; // 已借图书的书名（STL 容器，长度自动增长）

public:

    Student();                                                       
    Student(const std::string& name, const std::string& studentId);   

    // ---- 设置（修改）数据成员 ----
    void setName(const std::string& name);
    void setStudentId(const std::string& studentId);

   
    std::string getName() const;
    std::string getStudentId() const;
    int         getBorrowCount() const;      

    // 还能不能借（没借满就能借）
    bool canBorrow() const;


    bool borrowBook(Book& book);

    void showInfo() const;                   
};

#endif
