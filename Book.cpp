#include "Book.h"
#include <iostream>
using namespace std;


Book::Book()
    : name("未知书名"), isbn("0000000000000"), publisher("未知出版社"),
      price(0.0), pageCount(0), inLibrary(false) {
    cout << "[构造] 默认构造函数被调用：" << name << endl;
}


Book::Book(string name, string isbn, string publisher,
           double price, int pageCount, bool inLibrary)
    : name(name), isbn(isbn), publisher(publisher),
      price(price), pageCount(pageCount), inLibrary(inLibrary) {

    if (!isValidIsbn(this->isbn)) {
        cout << "[警告] ISBN 号不合法：" << this->isbn
             << "，已重置为默认值 0000000000000" << endl;
        this->isbn = "0000000000000";
    }
    if (this->price < 0) {
        cout << "[警告] 价格不能为负数，已重置为 0" << endl;
        this->price = 0.0;
    }
    if (this->pageCount < 0) {
        cout << "[警告] 页数不能为负数，已重置为 0" << endl;
        this->pageCount = 0;
    }
    cout << "[构造] 重载构造函数被调用：" << this->name << endl;
}


void Book::setName(const string& name) {
    this->name = name;              
}

void Book::setIsbn(const string& isbn) {

    if (!isValidIsbn(isbn)) {       
        cout << "[警告] ISBN 号不合法，修改被拒绝：" << isbn << endl;
        return;
    }
    this->isbn = isbn;
}

void Book::setPublisher(const string& publisher) {
    this->publisher = publisher;
}

void Book::setPrice(double price) {
    if (price < 0) {               
        cout << "[警告] 价格不能为负数，修改被拒绝" << endl;
        return;
    }
    this->price = price;
}

void Book::setPageCount(int pageCount) {
    if (pageCount < 0) {           
        cout << "[警告] 页数不能为负数，修改被拒绝" << endl;
        return;
    }
    this->pageCount = pageCount;
}

void Book::setInLibrary(bool inLibrary) {
    this->inLibrary = inLibrary;    
}

string Book::getName()      const { return name; }
string Book::getIsbn()      const { return isbn; }
string Book::getPublisher() const { return publisher; }
double Book::getPrice()     const { return price; }
int    Book::getPageCount() const { return pageCount; }
bool   Book::getInLibrary() const { return inLibrary; }


void Book::showInfo() const {
    cout << "-----------------------------" << endl;
    cout << "书名  : " << name << endl;
    cout << "ISBN  : " << isbn << endl;
    cout << "出版社: " << publisher << endl;
    cout << "价格  : " << price << " 元" << endl;
    cout << "页数  : " << pageCount << " 页" << endl;
    cout << "状态  : " << (inLibrary ? "在馆可借" : "已借出") << endl;
    cout << "-----------------------------" << endl;
}

// ---------- 验证 ISBN 合法性（static 函数：不需要对象就能调用）----------
// ISBN-13 完整规则，分三步：
//   第 1 步：去掉 '-' 后必须是 13 位数字；
//   第 2 步：前 12 位按 "1 倍、3 倍" 交替加权求和；
//   第 3 步：算出应有的校验位，与第 13 位比对。
//
// 举例 978-7-121-15535-2：
//   前 12 位  9 7 8 7 1 2 1 1 5 5 3 5
//   权重     1 3 1 3 1 3 1 3 1 3 1 3
//   乘积     9 21 8 21 1 6 1 3 5 15 3 15  → 和 = 108
//   108 % 10 = 8，10 - 8 = 2  →  校验位应为 2，实际第 13 位正是 2，合法。
bool Book::isValidIsbn(const string& isbn) {
    // ---------- 第 1 步：提取数字，剔除 '-' ----------
    string digits = "";          // 存去掉 '-' 之后的数字
    for (size_t i = 0; i < isbn.size(); ++i) {   // 逐个字符检查
        char c = isbn[i];
        if (c == '-') {
            continue;            // '-' 是分隔符，跳过
        }
        if (c < '0' || c > '9') {
            return false;        // 出现非数字字符 → 不合法
        }
        digits += c;
    }
    if (digits.size() != 13) {
        return false;            // 位数不是 13 → 不合法
    }

    // ---------- 第 2 步：前 12 位交替加权求和 ----------
    // digits[0] 权重 1，digits[1] 权重 3，digits[2] 权重 1 …… 依此类推
    int sum = 0;
    for (int i = 0; i < 12; ++i) {
        int d = digits[i] - '0';                 // 字符 → 数字：'9'-'0' = 9
        sum += (i % 2 == 0) ? (d * 1) : (d * 3); // 偶数下标 ×1，奇数下标 ×3
    }

    // ---------- 第 3 步：算校验位并与第 13 位比对 ----------
    // 目的：让 (加权和 + 校验位) 能被 10 整除
    // 外层再 %10 是为了处理 sum%10==0 的情况（10-0=10 不可能是一位数，应取 0）
    int expected = (10 - sum % 10) % 10;
    int actual   = digits[12] - '0';             // 实际第 13 位数字

    return expected == actual;
}
