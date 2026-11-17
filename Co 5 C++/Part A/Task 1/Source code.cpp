
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Abstract base class
class Bill
{
protected:
    int billNo;
    string customerName;
    string billingDate;

public:
    Bill(int no, string name, string date)
    {
        billNo = no;
        customerName = name;
        billingDate = date;
    }

    // Pure virtual functions
    virtual double total() const = 0;

    virtual string type() const = 0;

    // Virtual function
    virtual void print() const
    {
        cout << "Bill Number: " << billNo << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Billing Date: " << billingDate << endl;
    }

    // Virtual destructor
    virtual ~Bill()
    {
    }
};

// Electricity bill
class ElectricityBill : public Bill
{
    double units;
    double rate;
    double fixedCharge;

public:
    ElectricityBill(int no, string name, string date,
                    double u, double r, double fixed)
        : Bill(no, name, date)
    {
        units = u;
        rate = r;
        fixedCharge = fixed;
    }

    double total() const override
    {
        return units * rate + fixedCharge;
    }

    string type() const override
    {
        return "Electricity Bill";
    }

    void print() const override
    {
        cout << "\n--- ELECTRICITY BILL ---" << endl;
        Bill::print();
        cout << "Units Consumed: " << units << endl;
        cout << "Rate per Unit: Rs. " << rate << endl;
        cout << "Fixed Charge: Rs. " << fixedCharge << endl;
        cout << "Total Amount: Rs. " << total() << endl;
    }
};

// Water bill
class WaterBill : public Bill
{
    double units;
    double rate;
    double fixedCharge;

public:
    WaterBill(int no, string name, string date,
              double u, double r, double fixed)
        : Bill(no, name, date)
    {
        units = u;
        rate = r;
        fixedCharge = fixed;
    }

    double total() const override
    {
        return units * rate + fixedCharge;
    }

    string type() const override
    {
        return "Water Bill";
    }

    void print() const override
    {
        cout << "\n--- WATER BILL ---" << endl;
        Bill::print();
        cout << "Water Units: " << units << endl;
        cout << "Rate per Unit: Rs. " << rate << endl;
        cout << "Fixed Charge: Rs. " << fixedCharge << endl;
        cout << "Total Amount: Rs. " << total() << endl;
    }
};

// Telephone bill
class TelephoneBill : public Bill
{
    double monthlyCharge;
    int callMinutes;
    double ratePerMinute;

public:
    TelephoneBill(int no, string name, string date,
                  double charge, int minutes, double rate)
        : Bill(no, name, date)
    {
        monthlyCharge = charge;
        callMinutes = minutes;
        ratePerMinute = rate;
    }

    double total() const override
    {
        return monthlyCharge + callMinutes * ratePerMinute;
    }

    string type() const override
    {
        return "Telephone Bill";
    }

    void print() const override
    {
        cout << "\n--- TELEPHONE BILL ---" << endl;
        Bill::print();
        cout << "Monthly Charge: Rs. " << monthlyCharge << endl;
        cout << "Call Minutes: " << callMinutes << endl;
        cout << "Rate per Minute: Rs. " << ratePerMinute << endl;
        cout << "Total Amount: Rs. " << total() << endl;
    }
};

// Internet bill
class InternetBill : public Bill
{
    double planCharge;
    double extraGB;
    double ratePerGB;

public:
    InternetBill(int no, string name, string date,
                 double charge, double gb, double rate)
        : Bill(no, name, date)
    {
        planCharge = charge;
        extraGB = gb;
        ratePerGB = rate;
    }

    double total() const override
    {
        return planCharge + extraGB * ratePerGB;
    }

    string type() const override
    {
        return "Internet Bill";
    }

    void print() const override
    {
        cout << "\n--- INTERNET BILL ---" << endl;
        Bill::print();
        cout << "Plan Charge: Rs. " << planCharge << endl;
        cout << "Extra Data: " << extraGB << " GB" << endl;
        cout << "Rate per GB: Rs. " << ratePerGB << endl;
        cout << "Total Amount: Rs. " << total() << endl;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    // Create bill objects
    ElectricityBill e(101, "Ravi", "17-11-2026",
                      150, 8, 50);

    WaterBill w(102, "Kumar", "17-11-2026",
                20, 15, 30);

    TelephoneBill t(103, "Arun", "17-11-2026",
                    500, 100, 1.5);

    InternetBill i(104, "Priya", "17-11-2026",
                   799, 5, 50);

    // Array of base-class pointers
    Bill* bills[4] = {&e, &w, &t, &i};

    double dayTotal = 0;

    cout << "===== DAILY BILL DETAILS =====" << endl;

    // Process all bills using polymorphism
    for (int j = 0; j < 4; j++)
    {
        bills[j]->print();

        dayTotal += bills[j]->total();
    }

    cout << "\n===== DAILY BILL SUMMARY =====" << endl;

    cout << "Number of Bills: 4" << endl;
    cout << "Daily Total: Rs. " << dayTotal << endl;

    return 0;
}
