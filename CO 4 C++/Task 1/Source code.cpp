
#include <iostream>
#include <string>
using namespace std;

class Staff
{
protected:
    string name;
    int id;
    double basic;

public:
    Staff(string n, int i, double b)
        : name(n), id(i), basic(b)
    {
    }

    virtual double pay() = 0;

    virtual void display()
    {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Salary: " << pay() << endl;
    }

    virtual ~Staff()
    {
    }
};

class Professor : public Staff
{
    double research;

public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i, b), research(r)
    {
    }

    double pay() override
    {
        return basic + basic * 0.42 + research;
    }
};

class LabAssistant : public Staff
{
public:
    LabAssistant(string n, int i, double b)
        : Staff(n, i, b)
    {
    }

    double pay() override
    {
        return basic + basic * 0.42;
    }
};

class GuestFaculty : public Staff
{
    double hours, rate;

public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(n, i, 0), hours(h), rate(r)
    {
    }

    double pay() override
    {
        return hours * rate;
    }
};

int main()
{
    Staff* s[3];

    s[0] = new Professor("Ravi", 101, 50000, 10000);
    s[1] = new LabAssistant("Kumar", 102, 30000);
    s[2] = new GuestFaculty("Arun", 103, 40, 500);

    cout << "COLLEGE PAYROLL DETAILS" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << "\nStaff " << i + 1 << endl;
        s[i]->display();
    }

    for (int i = 0; i < 3; i++)
    {
        delete s[i];
    }

    return 0;
}
