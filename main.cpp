#include "Book.h"
#include "Student.h"        // 演示段要用到 Student
#include "Bookshelf.h"      // 演示段要用到 Bookshelf
#include <iostream>
#include <windows.h>        // 注意：必须在 using 之前，顺序别动（详见项目进度.md 第八节）
using namespace std;

// ============================================================
// 【实验二演示用】图书借阅过程
//   学生 张三 从书架「图书馆一楼」借书，演示两种类关系：
//     · 组合关系：书架 has 图书（Bookshelf 里嵌了 Book 数组）
//     · 依赖关系：学生 use 图书（borrowBook 的参数是 Book&）
// ============================================================
void demoBorrow() {

    cout << "##### 实验二：组合关系 & 依赖关系 演示 #####" << endl << endl;

    // ---------- 1. 建书架（组合关系）----------
    // 注意！这一行会先在屏幕上刷出 10 行 Book 的构造信息：
    //   书架里嵌了 Book books[10]，这 10 本书必须先"出生"，
    //   才轮到 Bookshelf 自己的构造函数体执行。
    //   这就是指导书实验思考题 1 的答案 —— 先构造内嵌成员，再构造本类。
    cout << "【1】创建书架（观察前面那 10 行 Book 构造信息）：" << endl;
    Bookshelf shelf("图书馆一楼");
    cout << endl;

    // ---------- 2. 上架三本书 ----------
    cout << "【2】往书架上放 3 本书：" << endl;
    Book b1("三体", "9787536692930", "重庆出版社", 23.0, 302, true);
    Book b2("C++ Primer", "978-7-121-15535-2", "电子工业出版社", 128.0, 848, true);
    Book b3("活着", "9787506365437", "作家出版社", 20.0, 191, true);

    shelf.addBook(b1);
    shelf.addBook(b2);
    shelf.addBook(b3);
    cout << endl;

    // ---------- 3. 显示书架藏书 ----------
    cout << "【3】书架现在的样子：" << endl;
    shelf.showAllBooks();

    // ---------- 4. 创建学生 ----------
    cout << "【4】创建学生：" << endl;
    Student stu("张三", "2024001");
    stu.showInfo();
    cout << endl;

    // ---------- 5. 借书：成功 ----------
    cout << "【5】张三借《三体》（在馆）→ 应该成功：" << endl;
    stu.borrowBook(b1);
    cout << endl;

    // ---------- 6. 再借同一本：失败 ----------
    // 这一步是"依赖关系"的精髓：
    //   b1 在【第 5 步】已经被借走了，它的 inLibrary 变成了 false。
    //   现在再借，borrowBook 的第二道判断会拦住。
    //   —— 说明第 5 步真的改到了 b1 本人（不是一份复印件）。
    cout << "【6】张三再借同一本《三体》（已借出）→ 应该失败：" << endl;
    stu.borrowBook(b1);
    cout << endl;

    // ---------- 7. 换一本借：成功 ----------
    cout << "【7】张三改借《活着》（在馆）→ 应该成功：" << endl;
    stu.borrowBook(b3);
    cout << endl;

    // ---------- 8. 看学生借了什么 ----------
    cout << "【8】张三的借阅情况：" << endl;
    stu.showInfo();

    cout << "##### 实验二演示结束 #####" << endl << endl;
}

int main() {

    SetConsoleOutputCP(65001);

    cout << "===== 实验一：类与对象 演示 =====" << endl << endl;

    // ---------- 1. 用默认构造函数创建对象 ----------
    cout << "【1】默认构造函数创建对象：" << endl;
    Book b1;                       // 此时自动调用 Book()
    b1.showInfo();
    cout << endl;

    // ---------- 2. 用重载构造函数创建对象 ----------
    cout << "【2】重载构造函数创建对象：" << endl;
    Book b2("C++ Primer", "978-7-121-15535-2", "电子工业出版社",
            128.0, 848, true);
    b2.showInfo();
    cout << endl;

    // ---------- 3. 修改数据成员（set 函数）----------
    cout << "【3】修改数据成员：" << endl;
    b1.setName("三体");
    b1.setIsbn("9787536692930");
    b1.setPublisher("重庆出版社");
    b1.setPrice(23.0);
    b1.setPageCount(302);
    b1.setInLibrary(true);
    b1.showInfo();
    cout << endl;

    // ---------- 4. 尝试写入非法数据，观察验证效果 ----------
    cout << "【4】合法性验证测试：" << endl;
    b1.setIsbn("123");                     // 位数不够 → 应被拒绝
    b1.setPrice(-5);                       // 负数 → 应被拒绝
    Book b3("坏书", "abc", "某出版社", -1, -1, true);   // 构造时非法 → 应被纠正
    b3.showInfo();
    cout << endl;

    // ---------- 5. 读取数据成员（get 函数）----------
    cout << "【5】获取数据成员：" << endl;
    cout << "b2 的书名是：" << b2.getName() << endl;
    cout << "b2 的价格是：" << b2.getPrice() << " 元" << endl;
    cout << "b2 是否在馆：" << (b2.getInLibrary() ? "是" : "否") << endl;
    cout << endl;

    // ---------- 6. 静态成员函数：直接用类名调用，测试 ISBN 校验 ----------
    cout << "【6】ISBN 合法性判断（含校验位算法）：" << endl;

    // 合法样例
    cout << "9787536692930   (三体，13位且校验位正确) -> "
         << (Book::isValidIsbn("9787536692930") ? "合法" : "不合法") << endl;
    cout << "978-7-121-15535-2 (带横线，校验位正确)   -> "
         << (Book::isValidIsbn("978-7-121-15535-2") ? "合法" : "不合法") << endl;

    // 不合法样例
    cout << "97875366        (位数不够)              -> "
         << (Book::isValidIsbn("97875366") ? "合法" : "不合法") << endl;
    cout << "9787536692931   (13位但校验位错)        -> "
         << (Book::isValidIsbn("9787536692931") ? "合法" : "不合法") << endl;
    cout << "978753669293X   (含字母)                -> "
         << (Book::isValidIsbn("978753669293X") ? "合法" : "不合法") << endl;
    cout << "978753669293   (只有12位)              -> "
         << (Book::isValidIsbn("978753669293") ? "合法" : "不合法") << endl;

    cout << endl << "说明：最后一位叫『校验位』，用前12位加权求和取模算出来。" << endl;
    cout << "      只要有一位数字抄错，校验位就对不上，系统会拒绝。" << endl;

    cout << endl << "===== 实验一演示结束（对象在 main 结束时自动析构）=====" << endl;

    cout << endl << endl;
    demoBorrow();      // ← 实验二演示（组合关系 + 依赖关系）

    return 0;
}
