
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

// Abstract Bill class
class Bill
{
public:
    virtual double total() const = 0;
    virtual string type() const = 0;

    virtual ~Bill() {}
};

// Outpatient bill
class OutPatientBill : public Bill
{
    double consultationFee;
    double medicineFee;

public:
    OutPatientBill(double consultation, double medicine)
    {
        consultationFee = consultation;
        medicineFee = medicine;
    }

    double total() const override
    {
        return consultationFee + medicineFee;
    }

    string type() const override
    {
        return "OutPatient";
    }
};

// Inpatient bill
class InPatientBill : public Bill
{
    double roomCharge;
    double treatmentCharge;

public:
    InPatientBill(double room, double treatment)
    {
        roomCharge = room;
        treatmentCharge = treatment;
    }

    double total() const override
    {
        return roomCharge + treatmentCharge;
    }

    string type() const override
    {
        return "InPatient";
    }
};

// Abstract Payer class
class Payer
{
public:
    virtual double amountCovered(const Bill& bill) const = 0;

    virtual string payerName() const = 0;

    virtual ~Payer() {}
};

// SelfPay class
class SelfPay : public Payer
{
public:
    double amountCovered(const Bill& bill) const override
    {
        return 0;
    }

    string payerName() const override
    {
        return "Self Pay";
    }
};

// Insurance class
class Insurance : public Payer
{
    double coverLimit;
    double coPayment;

public:
    Insurance(double limit, double copay)
    {
        coverLimit = limit;
        coPayment = copay;
    }

    double amountCovered(const Bill& bill) const override
    {
        double eligibleAmount =
            bill.total() * (100 - coPayment) / 100;

        return min(eligibleAmount, coverLimit);
    }

    string payerName() const override
    {
        return "Insurance";
    }
};

// Government Scheme class
class GovernmentScheme : public Payer
{
    double outpatientRate;
    double inpatientRate;

public:
    GovernmentScheme(double opRate, double ipRate)
    {
        outpatientRate = opRate;
        inpatientRate = ipRate;
    }

    double amountCovered(const Bill& bill) const override
    {
        if (bill.type() == "OutPatient")
        {
            return min(bill.total(), outpatientRate);
        }
        else if (bill.type() == "InPatient")
        {
            return min(bill.total(), inpatientRate);
        }

        return 0;
    }

    string payerName() const override
    {
        return "Government Scheme";
    }
};

// New payer class: Corporate Tie-Up
class CorporateTieUp : public Payer
{
    double coveragePercentage;
    double coverLimit;

public:
    CorporateTieUp(double percentage, double limit)
    {
        coveragePercentage = percentage;
        coverLimit = limit;
    }

    double amountCovered(const Bill& bill) const override
    {
        double amount =
            bill.total() * coveragePercentage / 100;

        return min(amount, coverLimit);
    }

    string payerName() const override
    {
        return "Corporate Tie-Up";
    }
};

int main()
{
    cout << fixed << setprecision(2);

    // Create bills
    OutPatientBill opBill(500, 1000);
    InPatientBill ipBill(4000, 8000);

    // Create payer objects
    SelfPay self;
    Insurance insurance(8000, 20);
    GovernmentScheme government(1000, 5000);
    CorporateTieUp corporate(80, 10000);

    // Array of payer pointers
    Payer* payers[4] =
    {
        &self,
        &insurance,
        &government,
        &corporate
    };

    // Array of bill pointers
    Bill* bills[2] =
    {
        &opBill,
        &ipBill
    };

    // Process all bills and payers
    for (int i = 0; i < 2; i++)
    {
        cout << "\n===== " << bills[i]->type()
             << " BILL =====" << endl;

        cout << "Total Bill Amount: Rs. "
             << bills[i]->total() << endl;

        for (int j = 0; j < 4; j++)
        {
            double covered =
                payers[j]->amountCovered(*bills[i]);

            double patientAmount =
                bills[i]->total() - covered;

            cout << "\nPayer: " << payers[j]->payerName() << endl;

            cout << "Amount Covered: Rs. "
                 << covered << endl;

            cout << "Patient Pays: Rs. "
                 << patientAmount << endl;
        }
    }

    return 0;
}
