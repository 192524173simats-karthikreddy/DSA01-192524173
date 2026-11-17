
#include <iostream>
#include <string>
using namespace std;

class Address
{
    string city;
    int pin;

public:
    Address(string c, int p) : city(c), pin(p)
    {
        cout << "Address Constructor" << endl;
    }

    string str() const
    {
        return city + "-" + to_string(pin);
    }

    ~Address()
    {
        cout << "Address Destructor" << endl;
    }
};

class Course
{
    string courseName;

public:
    Course(string c) : courseName(c)
    {
        cout << "Course Constructor" << endl;
    }

    void display()
    {
        cout << "Course: " << courseName << endl;
    }

    ~Course()
    {
        cout << "Course Destructor" << endl;
    }
};

class Person
{
protected:
    string name;
    int age;
    Address home;

public:
    Person(string n, int a, string city, int pin)
        : name(n), age(a), home(city, pin)
    {
        cout << "Person Constructor" << endl;
    }

    void displayPerson()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Address: " << home.str() << endl;
    }

    ~Person()
    {
        cout << "Person Destructor" << endl;
    }
};

class Student : virtual public Person
{
protected:
    long long regNo;
    Course course;

public:
    Student(string n, int a, long long r, string city, int pin,
            string c)
        : Person(n, a, city, pin),
          regNo(r), course(c)
    {
        cout << "Student Constructor" << endl;
    }

    void displayStudent()
    {
        displayPerson();
        cout << "Register Number: " << regNo << endl;
        course.display();
    }

    ~Student()
    {
        cout << "Student Destructor" << endl;
    }
};

class Staff : virtual public Person
{
protected:
    string department;

public:
    Staff(string n, int a, string city, int pin, string d)
        : Person(n, a, city, pin), department(d)
    {
        cout << "Staff Constructor" << endl;
    }

    void displayStaff()
    {
        displayPerson();
        cout << "Department: " << department << endl;
    }

    ~Staff()
    {
        cout << "Staff Destructor" << endl;
    }
};

class TeachingAssistant : public Student, public Staff
{
public:
    TeachingAssistant(string n, int a, long long r,
                      string city, int pin, string c, string d)
        : Person(n, a, city, pin),
          Student(n, a, r, city, pin, c),
          Staff(n, a, city, pin, d)
    {
        cout << "TeachingAssistant Constructor" << endl;
    }

    void display()
    {
        cout << "\nTEACHING ASSISTANT DETAILS" << endl;
        displayStudent();
        cout << "Department: " << department << endl;
    }

    ~TeachingAssistant()
    {
        cout << "TeachingAssistant Destructor" << endl;
    }
};

int main()
{
    cout << "STUDENT OBJECT" << endl;

    {
        Student s("Kavya", 19, 192311001,
                  "Salem", 636001, "C++");

        s.displayStudent();
    }

    cout << "\nSTAFF OBJECT" << endl;

    {
        Staff st("Ravi", 35, "Chennai", 600001, "CSE");

        st.displayStaff();
    }

    cout << "\nTEACHING ASSISTANT OBJECT" << endl;

    {
        TeachingAssistant ta("Arun", 25, 192311002,
                             "Salem", 636001, "Java", "CSE");

        ta.display();
    }

    return 0;
}
