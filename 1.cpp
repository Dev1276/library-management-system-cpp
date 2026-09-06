#include <bits/stdc++.h>
using namespace std;

class Person{
protected:
    int id;
    string name;
    string email_id;
    string phone_no;
   
public:

    Person(int pid,string nm,string email,string no){
        id = pid;
        name = nm;
        email_id = email;
        phone_no = no;
    }

    int getId(){
        return id;
    }

    string getName(){
        return name;
    }

    string getEmailId(){
        return email_id;
    }

    string getPhoneNo(){
        return phone_no;
    }
};

class Book
{
private:
    int book_id;
    string title;
    string author;
    int borrowed_by;

public:
    Book(int bid, string ttl, string athr)
    {
        book_id = bid;
        title = ttl;
        author = athr;
        borrowed_by = -1;
    }

    int getBookId()
    {
        return book_id;
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    int getBorrowedBy()
    {
        return borrowed_by;
    }

    void setBorrowedBy(int k)
    {
        borrowed_by = k;
    }
};

class Member : public Person
{
private:

    vector<int> borrowed_books;

public:
    Member(int id, string nm, string em, string pn) : Person(id,nm,em,pn)
    {

    }

    vector<int> getBorrowedBooks()
    {
        return borrowed_books;
    }

    void addBorrowedBooks(int bookId)
    {
        auto it = find(borrowed_books.begin(), borrowed_books.end(), bookId);
        if (it != borrowed_books.end())
        {
            cout << "Book already exist" << endl;
            return; // already has this book, don't add duplicate
        }
        borrowed_books.push_back(bookId);
    }

    void removeBorrowedBooks(int bookId)
    {
        auto it = find(borrowed_books.begin(), borrowed_books.end(), bookId);
        if (it == borrowed_books.end())
        {
            cout << "Book DNE nothing tp remove" << endl;
            return; // bookId not found, nothing to remove
        }
        int k = it - borrowed_books.begin();
        for (int i = k; i < borrowed_books.size() - 1; i++)
        {
            borrowed_books[i] = borrowed_books[i + 1];
        }
        borrowed_books.pop_back();
    }
};

class Librarian : public Person
{
public:
    Librarian(int id,string name,string email, string no) : Person(id,name,email,no){};
};

class Library
{
private:
    map<int, Member> members;
    map<int, Book> books;

public:
    void addBook(int bid, string ttl, string athr)
    {
        if (books.find(bid) == books.end())
            books.emplace(bid, Book(bid, ttl, athr));
        else
            cout << "Book already exists" << endl;
    }

    void registerMember(int id, string nm, string em, string no)
    {
        if (members.find(id) == members.end())
            members.emplace(id, Member(id,nm,em,no));
        else
            cout << "Member already exists" << endl;
    }

    void issueBook(int bid, int mid)
    {
        if (books.find(bid) == books.end())
        {
            cout << "Book with id: " << bid << " does not exist" << endl;
            return;
        }

        if (members.find(mid) == members.end())
        {
            cout << "Member with id: " << mid << " does not exist" << endl;
            return;
        }

        if (books.at(bid).getBorrowedBy() != -1)
        {
            cout << "Sorry, book with id: " << bid << " is already issued" << endl;
        }
        else
        {
            books.at(bid).setBorrowedBy(mid);
            members.at(mid).addBorrowedBooks(bid);
        }
    }

    void returnBook(int bid, int mid)
    {
        if (books.find(bid) == books.end())
        {
            cout << "Book DNE so u cant return" << endl;
            return;
        }

        if (members.find(mid) == members.end())
        {
            cout << "Members is not registered" << endl;
            return;
        }

        if (books.at(bid).getBorrowedBy() != mid)
        {
            cout << "book is issued to different member u cant return it" << endl;
            return;
        }
        else
        {
            books.at(bid).setBorrowedBy(-1);
            members.at(mid).removeBorrowedBooks(bid);
            cout << "Thank You for returning book" << endl;
            return;
        }
    }

    void displayAllBooks(){
        cout << "Total Books in Library: " << books.size() << endl;
        for(auto &pair : books){
            cout << "Book Id: " << pair.first << " | "; 
            cout << "Book Title: " << pair.second.getTitle() << " | "; 
            cout << "Book Author: " << pair.second.getAuthor() << " | ";
            if(pair.second.getBorrowedBy() == -1)
                cout << "Available" << endl;
            else 
                cout << "Book Borrowed by member: " << pair.second.getBorrowedBy() << endl;
        }
        return;
    }
};

int main()
{
    Library lib;
    lib.addBook(1,"Science","S Chand");
    lib.addBook(2,"Maths","Rd Sharma");
    lib.addBook(3,"Hindi","Prem Chand");
    lib.registerMember(101,"Devansh","devgarg1276@gmail.com","9571201276");
    lib.registerMember(102,"Vishh","visemail","88997");
    lib.issueBook(2,101);
    lib.issueBook(1,102);
    lib.returnBook(2,101);
    
    lib.displayAllBooks();
    return 0;
}