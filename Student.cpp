#include "Student.h"
#include <iostream>
using namespace std;

Student::Student()
    : name("未填写"), studentId("00000000") {
    // borrowedTitles 是 vector，默认就是"空的"，无需在初始化列表里写
    cout << "[构造] Student 默认构造函数：学生 " << name << endl;
}


Student::Student(const string& name, const string& studentId)
    : name(name), studentId(studentId) {
    cout << "[构造] Student 重载构造函数：学生 " << this->name << endl;
}


void Student::setName(const string& name) {
    this->name = name;
}

void Student::setStudentId(const string& studentId) {
    this->studentId = studentId;
}


string Student::getName() const {
    return name;
}

string Student::getStudentId() const {
    return studentId;
}

int Student::getBorrowCount() const {
    // vector 的 size() 返回 size_t（无符号），转成 int 再返回
    return static_cast<int>(borrowedTitles.size());
}


bool Student::canBorrow() const {
    // 用 vector 的 size() 代替原来的 borrowCount
    return static_cast<int>(borrowedTitles.size()) < MAX_BORROW;
}


bool Student::borrowBook(Book& book) {

    // 第一关：学生还能不能借（没借满就能借）
    if (!canBorrow()) {
        cout << "借书失败：已达借阅上限（" << MAX_BORROW << " 本）" << endl;
        return false;
    }

    // 第二关：这本书在馆吗？（已被借出就不能再借）
    if (!book.getInLibrary()) {
        cout << "借书失败：《" << book.getName() << "》已被借出" << endl;
        return false;
    }

    // 两道关都过 → 动手改状态
    book.setInLibrary(false);                  // 书：在馆 → 已借出
    borrowedTitles.push_back(book.getName());  // 学生：书名追加到 vector 末尾（自动扩容）


    cout << "借书成功：" << name << " 借走了《" << book.getName() << "》" << endl;
    return true;

}


void Student::showInfo() const {
    cout << "-----------------------------" << endl;
    cout << "姓名  : " << name << endl;
    cout << "学号  : " << studentId << endl;
    cout << "已借  : " << borrowedTitles.size() << " / " << MAX_BORROW << " 本" << endl;

    if (!borrowedTitles.empty()) {
        cout << "书目  : ";
        bool first = true;

        for (const string& title : borrowedTitles) {
            if (!first) cout << "、";
            cout << title;
            first = false;
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}
