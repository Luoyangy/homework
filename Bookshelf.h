#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <string>
#include "Book.h"          



const int SHELF_CAPACITY = 10;

class Bookshelf {
private:

    std::string name;                    // 书架名称
    Book books[SHELF_CAPACITY];          // 图书对象数组 
    int  bookCount;                      // 当前已上架数量

public:

    Bookshelf();                                 
    Bookshelf(const std::string& name);        

    void setName(const std::string& name);
    std::string getName() const;
    int  getBookCount() const;
    int  getCapacity() const;

    bool addBook(const Book& book);

  
    void showAllBooks() const;
};

#endif
