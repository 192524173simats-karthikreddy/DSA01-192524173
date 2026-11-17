
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

// Abstract Bill class
class Bill
{
protected:
    string patient;

public:
    explicit Bill(const string& p)
    {
        patient = p;
    }

    virtual ~Bill() = default;

    // TODO 1: Pure virtual function
    virtual double total() const = 0;

    virtual string type() const
    {
        return "Bill";
    }

    void print() const
    {
        cout << type() << " " << patient
             << ": " << total() << endl;
    }
};

// OutPatient class
class OutPatient : public Bill
{
    double consultation, tests;

public:
    OutPatient(const string& p, double c, double t)
        : Bill(p), consultation(c), tests(t)
    {
    }

    // TODO 2: Override total() and type()
    double total() const override
    {
        return consultation + tests;
    }

    string type() const override
    {
        return "OP";
    }
};

// InPatient class
class InPatient : public Bill
{
    int days;
    double perDay, surgery;

public:
    InPatient(const string& p, int d, double rate, double s)
        : Bill(p), days(d), perDay(rate), surgery(s)
    {
    }

    // TODO 3: Override total() and type()
    double total() const override
    {
        return days * perDay + surgery;
    }

    string type() const override
    {
        return "IP";
    }
};

// Abstract Payer class
class Payer
{
public:
    virtual double amountCovered(const Bill& bill) const = 0;

    virtual string name() const = 0;

    virtual ~Payer() = default;
};

// SelfPay class
class SelfPay : public Payer
{
public:
    double amountCovered(const Bill& bill) const override
    {
        return 0;
    }

    string name() const override
    {
        return "SelfPay";
    }
};

// Insurance class
class Insurance : public Payer
{
    double coverLimit;
    double coPayment;

public:
    Insurance(double limit, double copay)
        : coverLimit(limit), coPayment(copay)
    {
    }

    double amountCovered(const Bill& bill) const override
    {
        double amount = bill.total() * (100 - coPayment) / 100;
        return min(amount, coverLimit);
    }

    string name() const override
    {
        return "Insurance";
    }
};

// Government Scheme class
class GovernmentScheme : public Payer
{
    double opRate, ipRate;

public:
    GovernmentScheme(double op, double ip)
        : opRate(op), ipRate(ip)
    {
    }

    double amountCovered(const Bill& bill) const override
    {
        if (bill.type() == "OP")
            return min(bill.total(), opRate);

        if (bill.type() == "IP")
            return min(bill.total(), ipRate);

        return 0;
    }

    string name() const override
    {
        return "GovernmentScheme";
    }
};

// Corporate Tie-Up class
class CorporateTieUp : public Payer
{
    double percentage;
    double coverLimit;

public:
    CorporateTieUp(double percent, double limit)
        : percentage(percent), coverLimit(limit)
    {
    }

    double amountCovered(const Bill& bill) const override
    {
        double amount = bill.total() * percentage / 100;
        return min(amount, coverLimit);
    }

    string name() const override
    {
        return "CorporateTieUp";
    }
};

int main()
{
    cout << fixed << setprecision(2);

    // Create bill objects
    Bill* bills[2] =
    {
        new OutPatient("Ravi", 500, 1200),
        new InPatient("Meena", 3, 2500, 40000)
    };

    // Create payer objects
    Payer* payers[4] =
    {
        new SelfPay(),
        new Insurance(50000, 20),
        new GovernmentScheme(1000, 30000),
        new CorporateTieUp(90, 40000)
    };

    double sum = 0;

    cout << "===== BILL DETAILS =====" << endl;

    for (int i = 0; i < 2; i++)
    {
        bills[i]->print();
        sum += bills[i]->total();
    }

    cout << "Total " << sum << endl;

    cout << "\n===== PAYER COVERAGE DETAILS =====" << endl;

    for (int i = 0; i < 2; i++)
    {
        cout << "\nBill Type: " << bills[i]->type() << endl;
        cout << "Bill Amount: Rs. " << bills[i]->total() << endl;

        for (int j = 0; j < 4; j++)
        {
            double covered = payers[j]->amountCovered(*bills[i]);

            double patientPays = bills[i]->total() - covered;

            cout << "\nPayer: " << payers[j]->name() << endl;
            cout << "Amount Covered: Rs. " << covered << endl;
            cout << "Patient Pays: Rs. " << patientPays << endl;
        }
    }

    // Delete payer objects
    for (int i = 0; i < 4; i++)
    {
        delete payers[i];
    }

    // Delete bill objects
    for (int i = 0; i < 2; i++)
    {
        delete bills[i];
    }

    return 0;
}
