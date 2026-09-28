#include "Bookshelf.h"
#include <iostream>
using namespace std;

Bookshelf::Bookshelf()
    : name("未命名书架"), bookCount(0) {
    cout << "[构造] Bookshelf 默认构造函数：书架 " << name << endl;
}

Bookshelf::Bookshelf(const string& name)
    : name(name), bookCount(0) {
    cout << "[构造] Bookshelf 重载构造函数：书架 " << this->name << endl;
}


void Bookshelf::setName(const string& name) {
    this->name = name;
}

string Bookshelf::getName() const {
    return name;
}

int Bookshelf::getBookCount() const {
    return bookCount;
}

int Bookshelf::getCapacity() const {
    return SHELF_CAPACITY;
}


bool Bookshelf::addBook(const Book& book) {


    if (bookCount >= SHELF_CAPACITY) {
        cout << "上架失败：书架已满（最多 " << SHELF_CAPACITY << " 本）" << endl;
        return false;
    }

    books[bookCount] = book;
    ++bookCount;

    cout << "上架成功：" << book.getName() << " 已放入「" << name << "」" << endl;
    return true;
}

void Bookshelf::showAllBooks() const {
    cout << "===== 书架「" << name << "」 共 "
         << bookCount << " / " << SHELF_CAPACITY << " 本 =====" << endl;

    if (bookCount == 0) {
        cout << "（书架是空的）" << endl;
    } else {
        for (int i = 0; i < bookCount; ++i) {
            cout << "  " << (i + 1) << ". " << books[i].getName()
                 << "   [" << (books[i].getInLibrary() ? "在馆可借" : "已借出") << "]"
                 << endl;
        }
    }
    cout << endl;
}
