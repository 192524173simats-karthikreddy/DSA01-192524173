
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
using namespace std;

class Bill
{
protected:
    string billNo;
    double amount;

public:
    Bill(string no, double a) : billNo(no), amount(a)
    {
        if (a < 0)
            throw invalid_argument("Negative bill amount");
    }

    virtual double total() const = 0;
    virtual string type() const = 0;

    virtual void display() const
    {
        cout << billNo << "\t" << type()
             << "\tRs. " << total() << endl;
    }

    virtual ~Bill() {}
};

class OutPatientBill : public Bill
{
    double tests;

public:
    OutPatientBill(string no, double consultation, double t)
        : Bill(no, consultation + t), tests(t) {}

    double total() const override
    {
        return amount;
    }

    string type() const override
    {
        return "OutPatient";
    }
};

class InPatientBill : public Bill
{
    int days;
    double dailyRate;
    double surgery;

public:
    InPatientBill(string no, int d, double rate, double s)
        : Bill(no, d * rate + s),
          days(d), dailyRate(rate), surgery(s) {}

    double total() const override
    {
        return days * dailyRate + surgery;
    }

    string type() const override
    {
        return "InPatient";
    }
};

class TelephoneBill : public Bill
{
    double minutes;
    double rate;

public:
    TelephoneBill(string no, double base, double m, double r)
        : Bill(no, base + m * r), minutes(m), rate(r) {}

    double total() const override
    {
        return amount;
    }

    string type() const override
    {
        return "Telephone";
    }
};

class Payer
{
public:
    virtual double coverage(const Bill& bill) const = 0;
    virtual string name() const = 0;
    virtual ~Payer() {}
};

class SelfPay : public Payer
{
public:
    double coverage(const Bill&) const override
    {
        return 0;
    }

    string name() const override
    {
        return "Self Pay";
    }
};

class Insurance : public Payer
{
    double percentage;
    double limit;

public:
    Insurance(double p, double l) : percentage(p), limit(l) {}

    double coverage(const Bill& bill) const override
    {
        return min(bill.total() * percentage / 100, limit);
    }

    string name() const override
    {
        return "Insurance";
    }
};

class GovernmentPayer : public Payer
{
    double limit;

public:
    GovernmentPayer(double l) : limit(l) {}

    double coverage(const Bill& bill) const override
    {
        return min(bill.total() * 0.80, limit);
    }

    string name() const override
    {
        return "Government";
    }
};

class CorporatePayer : public Payer
{
    double percentage;

public:
    CorporatePayer(double p) : percentage(p) {}

    double coverage(const Bill& bill) const override
    {
        return bill.total() * percentage / 100;
    }

    string name() const override
    {
        return "Corporate";
    }
};

class PharmacyBill : public Bill
{
    int quantity;
    double unitPrice;
    double dispensingFee;

public:
    PharmacyBill(string no, int q, double price, double fee)
        : Bill(no, q * price + fee),
          quantity(q), unitPrice(price), dispensingFee(fee)
    {
        if (q < 0 || price < 0 || fee < 0)
            throw invalid_argument("Invalid pharmacy bill details");
    }

    double total() const override
    {
        return quantity * unitPrice + dispensingFee;
    }

    string type() const override
    {
        return "Pharmacy";
    }
};

class CharityPayer : public Payer
{
    double percentage;
    double limit;

public:
    CharityPayer(double p, double l) : percentage(p), limit(l) {}

    double coverage(const Bill& bill) const override
    {
        return min(bill.total() * percentage / 100, limit);
    }

    string name() const override
    {
        return "Charity";
    }
};

void validateClaim(double amount, double limit)
{
    if (amount < 0 || limit < 0)
        throw invalid_argument("Negative claim amount");

    if (amount > limit)
        throw runtime_error("Claim exceeds limit");
}

struct BillRule
{
    string name;
    double fixedAmount;
    double rate;
};

struct PayerRule
{
    string name;
    double percentage;
    double limit;
};

double calculatePluginBill(double quantity, const BillRule& rule)
{
    if (quantity < 0 || rule.fixedAmount < 0 || rule.rate < 0)
        throw invalid_argument("Invalid bill rule");

    return rule.fixedAmount + quantity * rule.rate;
}

double calculatePluginCoverage(double total, const PayerRule& rule)
{
    if (total < 0 || rule.percentage < 0 || rule.limit < 0)
        throw invalid_argument("Invalid payer rule");

    return min(total * rule.percentage / 100, rule.limit);
}

int main()
{
    cout << fixed << setprecision(2);

    cout << "===== HOSPITAL BILLING SYSTEM =====\n";

    vector<unique_ptr<Bill>> bills;

    bills.push_back(make_unique<OutPatientBill>("B101", 1000, 500));
    bills.push_back(make_unique<InPatientBill>("B102", 3, 2000, 5000));
    bills.push_back(make_unique<TelephoneBill>("B103", 300, 100, 2));
    bills.push_back(make_unique<PharmacyBill>("B104", 5, 200, 50));

    vector<unique_ptr<Payer>> payers;

    payers.push_back(make_unique<SelfPay>());
    payers.push_back(make_unique<Insurance>(80, 50000));
    payers.push_back(make_unique<GovernmentPayer>(30000));
    payers.push_back(make_unique<CorporatePayer>(90));
    payers.push_back(make_unique<CharityPayer>(50, 2000));

    cout << "\nB4.1 BILL DETAILS\n";
    cout << "Bill No.\tBill Type\tAmount\n";

    for (const auto& bill : bills)
        bill->display();

    cout << "\nPAYER COVERAGE DETAILS\n";

    for (const auto& bill : bills)
    {
        cout << "\nBill: " << bill->type()
             << " | Total: Rs. " << bill->total() << endl;

        for (const auto& payer : payers)
        {
            cout << payer->name()
                 << " Coverage: Rs. "
                 << payer->coverage(*bill) << endl;
        }
    }

    cout << "\nB4.2 EXCEPTION TESTING\n";

    try
    {
        validateClaim(60000, 50000);
    }
    catch (const exception& e)
    {
        cout << "Caught Exception: " << e.what() << endl;
    }

    try
    {
        OutPatientBill invalidBill("B105", 1000, -500);
        cout << invalidBill.total() << endl;
    }
    catch (const exception& e)
    {
        cout << "Caught Exception: " << e.what() << endl;
    }

    cout << "\nB4.3 CONFIGURATION-BASED PLUGIN TEST\n";

    BillRule pharmacyRule = {"Pharmacy", 50, 200};
    PayerRule charityRule = {"Charity", 50, 2000};

    double pluginBill = calculatePluginBill(5, pharmacyRule);
    double pluginCoverage = calculatePluginCoverage(pluginBill, charityRule);

    cout << "Plugin Bill Type: " << pharmacyRule.name << endl;
    cout << "Plugin Bill Total: Rs. " << pluginBill << endl;
    cout << "Plugin Payer: " << charityRule.name << endl;
    cout << "Plugin Coverage: Rs. " << pluginCoverage << endl;

    cout << "\nAll billing tests completed successfully.\n";

    return 0;
}
