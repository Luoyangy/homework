#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:

    std::string name;        // 图书名称
    std::string isbn;        // ISBN 号
    std::string publisher;   // 出版社
    double price;            // 价格
    int    pageCount;        // 页数
    bool   inLibrary;        // 在馆状态：true = 在馆可借，false = 已借出

public:

    Book();                            
    Book(std::string name, std::string isbn, std::string publisher,
         double price, int pageCount, bool inLibrary);  


    void setName(const std::string& name);
    void setIsbn(const std::string& isbn);          
    void setPublisher(const std::string& publisher);
    void setPrice(double price);                    
    void setPageCount(int pageCount);               
    void setInLibrary(bool inLibrary);             

    std::string getName() const;
    std::string getIsbn() const;
    std::string getPublisher() const;
    double getPrice() const;
    int    getPageCount() const;
    bool   getInLibrary() const;                    

    void showInfo() const;                         

    static bool isValidIsbn(const std::string& isbn);
};

#endif
