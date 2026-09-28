#include "Student.h"
#include <iostream>
using namespace std;    // .cpp 里写 using 不会影响别的文件，可以图省事

// ========== 构造函数 ==========

// 默认构造函数：vector 成员会自动默认构造为空容器，不用手动清空
Student::Student()
    : name("未填写"), studentId("00000000") {
    // borrowedTitles 是 vector，默认就是"空的"，无需在初始化列表里写
    cout << "[构造] Student 默认构造函数：学生 " << name << endl;
}

// 重载构造函数：name(name) 括号外是成员、括号内是参数（同名靠位置区分）
Student::Student(const string& name, const string& studentId)
    : name(name), studentId(studentId) {
    cout << "[构造] Student 重载构造函数：学生 " << this->name << endl;
}

// ========== 设置数据成员 ==========
void Student::setName(const string& name) {
    this->name = name;          // this->name 是成员，name 是参数
}

void Student::setStudentId(const string& studentId) {
    this->studentId = studentId;
}

// ========== 获取数据成员（只读）==========
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

// ========== 还能不能借 ==========
bool Student::canBorrow() const {
    // 用 vector 的 size() 代替原来的 borrowCount
    return static_cast<int>(borrowedTitles.size()) < MAX_BORROW;
}

// ========== ★★ 实验二核心：借书（依赖关系）★★ ==========
// 要同时看两边：学生借满了没？书在馆吗？两边都放行才算成功。
bool Student::borrowBook(Book& book) {

    // 第一关：学生自己借满了吗？
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
                                               // 原来的写法要自己算下标，现在一行搞定

    cout << "借书成功：" << name << " 借走了《" << book.getName() << "》" << endl;
    return true;

}

// ========== 输出学生信息 ==========
void Student::showInfo() const {
    cout << "-----------------------------" << endl;
    cout << "姓名  : " << name << endl;
    cout << "学号  : " << studentId << endl;
    cout << "已借  : " << borrowedTitles.size() << " / " << MAX_BORROW << " 本" << endl;

    if (!borrowedTitles.empty()) {         // empty() 判断容器是否为空
        cout << "书目  : ";
        bool first = true;
        // 范围 for：自动遍历 vector 里每一个书名，不用管下标
        for (const string& title : borrowedTitles) {
            if (!first) cout << "、";      // 书名之间用顿号分隔
            cout << title;
            first = false;
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}
