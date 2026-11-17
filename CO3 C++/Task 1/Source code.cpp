
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book
{
    string title;
    int copies;

public:
    Book() : Book("", 0)
    {
    }

    Book(string t) : Book(t, 1)
    {
    }

    Book(string t, int c) : title(t), copies(c)
    {
        if (c < 0)
        {
            throw invalid_argument("Copies cannot be negative");
        }
    }

    void display()
    {
        cout << "Title: " << title << endl;
        cout << "Copies: " << copies << endl;
        cout << "------------------" << endl;
    }
};

int main()
{
    try
    {
        Book b1;
        Book b2("C++ Programming");
        Book b3("Python Programming", 10);

        cout << "Book 1:" << endl;
        b1.display();

        cout << "Book 2:" << endl;
        b2.display();

        cout << "Book 3:" << endl;
        b3.display();

        Book b4("Java Programming", -5);
        b4.display();
    }
    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
