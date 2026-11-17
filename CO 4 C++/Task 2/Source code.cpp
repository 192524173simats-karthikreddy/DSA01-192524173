
#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;
    int id;
    string phone;

public:
    Person(string n, int i, string p)
        : name(n), id(i), phone(p)
    {
    }

    void displayPerson()
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Phone: " << phone << endl;
    }
};

class Student : virtual public Person
{
protected:
    string programme;
    double cgpa;

public:
    Student(string n, int i, string p, string prog, double c)
        : Person(n, i, p), programme(prog), cgpa(c)
    {
    }

    void displayStudent()
    {
        cout << "Programme: " << programme << endl;
        cout << "CGPA: " << cgpa << endl;
    }
};

class Staff : virtual public Person
{
protected:
    string department;
    double salary;

public:
    Staff(string n, int i, string p, string d, double s)
        : Person(n, i, p), department(d), salary(s)
    {
    }

    void displayStaff()
    {
        cout << "Department: " << department << endl;
        cout << "Salary: " << salary << endl;
    }
};

class TeachingAssistant : public Student, public Staff
{
public:
    TeachingAssistant(string n, int i, string p, string prog,
                      double c, string d, double s)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          Staff(n, i, p, d, s)
    {
    }

    void display()
    {
        cout << "\nTEACHING ASSISTANT DETAILS" << endl;
        displayPerson();
        displayStudent();
        displayStaff();
    }
};

class ResearchScholar : public Student
{
    double fellowship;

public:
    ResearchScholar(string n, int i, string p, string prog,
                    double c, double f)
        : Person(n, i, p),
          Student(n, i, p, prog, c),
          fellowship(f)
    {
    }

    void display()
    {
        cout << "\nRESEARCH SCHOLAR DETAILS" << endl;
        displayPerson();
        displayStudent();
        cout << "Fellowship: " << fellowship << endl;
    }
};

int main()
{
    TeachingAssistant ta("Ravi", 101, "9876543210",
                         "AI & DS", 9.1, "CSE", 30000);

    ResearchScholar rs("Kumar", 102, "9876501234",
                       "Computer Science", 9.5, 15000);

    ta.display();
    rs.display();

    return 0;
}
