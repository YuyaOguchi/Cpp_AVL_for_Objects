#pragma once
#include <string>

class Book{
public:
    Book(){}
    Book(std::string authornew, std::string namenew, std::string ISBNnew, std::string datenew){
        this->author = authornew;
        this->name = namenew;
        this->ISBN = ISBNnew;
        this->date = datenew;
    }

    std::string getAuthor(){return author;}
    std::string getName(){return name;}
    std::string getISBN(){return ISBN;}
    std::string getDate(){return date;}

    bool operator>(Book other) {return author.compare(other.author) > 0;}
    bool operator<(Book other) {return author.compare(other.author) < 0;}
    bool operator>=(Book other) {return author.compare(other.author) >= 0;}
    bool operator<=(Book other) {return author.compare(other.author) <= 0;}
    friend std::ostream& operator<<(std::ostream& out, Book& book);
private:
    std::string author;
    std::string name;
    std::string ISBN;
    std::string date;
};

std::ostream& operator<<(std::ostream& out, Book& book) {
    //out << "Name: " << book.getName() << std::endl;
    //out << "ISBN: " << book.getISBN() << std::endl;
    out << "Author: " << book.getAuthor() << std::endl;
    //out << "Date: " << book.getDate() << std::endl;
    return out;
}
