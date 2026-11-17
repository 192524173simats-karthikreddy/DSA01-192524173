
#include <iostream>
using namespace std;

class Account
{
public:
    double rate() const
    {
        return 3.5;
    }

    virtual double vrate() const
    {
        return 3.5;
    }

    virtual void display() const
    {
        cout << "Account Interest: " << vrate() << "%" << endl;
    }

    virtual ~Account()
    {
        cout << "Account Destructor" << endl;
    }
};

class SeniorAccount : public Account
{
    double* history;

public:
    SeniorAccount()
    {
        history = new double[100];
        cout << "Senior Account Created" << endl;
    }

    double rate() const
    {
        return 4.0;
    }

    double vrate() const override
    {
        return 4.0;
    }

    void display() const override
    {
        cout << "Senior Account Interest: " << vrate() << "%" << endl;
    }

    ~SeniorAccount()
    {
        delete[] history;
        cout << "Senior Account Memory Released" << endl;
        cout << "Senior Account Destructor" << endl;
    }
};

int main()
{
    Account* accounts[2];

    accounts[0] = new Account;
    accounts[1] = new SeniorAccount;

    cout << "\nBANK ACCOUNT DETAILS" << endl;

    for (Account* a : accounts)
    {
        a->display();
    }

    cout << "\nDELETING ACCOUNTS" << endl;

    for (Account* a : accounts)
    {
        delete a;
    }

    cout << "\nOBJECT SLICING TEST" << endl;

    SeniorAccount s;
    Account copy = s;

    cout << "Normal rate: " << copy.rate() << endl;
    cout << "Virtual rate: " << copy.vrate() << endl;

    cout << "\nUNIQUE POINTER TEST" << endl;

    return 0;
}
