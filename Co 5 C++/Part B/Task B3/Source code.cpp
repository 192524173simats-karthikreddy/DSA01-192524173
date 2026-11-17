
#include <iostream>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

volatile double resultValue = 0;

struct BillData
{
    int type;
    double a, b, fee;
};

BillData makeBill(int i)
{
    BillData bill;
    bill.type = i % 3;
    bill.a = 100 + (i % 500);
    bill.b = 10 + (i % 100);
    bill.fee = 50 + (i % 50);
    return bill;
}

class Bill
{
public:
    virtual double total() const = 0;
    virtual ~Bill() {}
};

class OutPatientBill : public Bill
{
    double a, b, fee;

public:
    OutPatientBill(double x, double y, double z)
        : a(x), b(y), fee(z) {}

    double total() const
    {
        return a + b + fee;
    }
};

class InPatientBill : public Bill
{
    double days, rate, fee;

public:
    InPatientBill(double x, double y, double z)
        : days(x), rate(y), fee(z) {}

    double total() const
    {
        return days * rate + fee;
    }
};

class TelephoneBill : public Bill
{
    double base, minutes, rate;

public:
    TelephoneBill(double x, double y, double z)
        : base(x), minutes(y), rate(z) {}

    double total() const
    {
        return base + minutes * rate;
    }
};

double switchTotal(const BillData& b)
{
    switch (b.type)
    {
        case 0: return b.a + b.b + b.fee;
        case 1: return b.a * b.b + b.fee;
        case 2: return b.a + b.b * b.fee;
    }

    return 0;
}

double virtualBenchmark(int n)
{
    vector<OutPatientBill> op;
    vector<InPatientBill> ip;
    vector<TelephoneBill> phone;
    vector<Bill*> bills;

    op.reserve(n / 3 + 1);
    ip.reserve(n / 3 + 1);
    phone.reserve(n / 3 + 1);
    bills.reserve(n);

    for (int i = 0; i < n; i++)
    {
        BillData b = makeBill(i);

        if (b.type == 0)
        {
            op.emplace_back(b.a, b.b, b.fee);
            bills.push_back(&op.back());
        }
        else if (b.type == 1)
        {
            ip.emplace_back(b.a, b.b, b.fee);
            bills.push_back(&ip.back());
        }
        else
        {
            phone.emplace_back(b.a, b.b, b.fee);
            bills.push_back(&phone.back());
        }
    }

    double sum = 0;
    high_resolution_clock::time_point start = high_resolution_clock::now();

    for (int i = 0; i < n; i++)
        sum += bills[i]->total();

    high_resolution_clock::time_point stop = high_resolution_clock::now();

    resultValue = sum;

    return duration<double, milli>(stop - start).count();
}

double switchBenchmark(int n)
{
    vector<BillData> bills;
    bills.reserve(n);

    for (int i = 0; i < n; i++)
        bills.push_back(makeBill(i));

    double sum = 0;
    high_resolution_clock::time_point start = high_resolution_clock::now();

    for (int i = 0; i < n; i++)
        sum += switchTotal(bills[i]);

    high_resolution_clock::time_point stop = high_resolution_clock::now();

    resultValue = sum;

    return duration<double, milli>(stop - start).count();
}

bool validateReturnCode(double amount)
{
    return amount >= 0;
}

void validateException(double amount)
{
    if (amount < 0)
        throw invalid_argument("Invalid bill amount");
}

double returnCodeBenchmark(int n, int percentage)
{
    int errors = 0;

    high_resolution_clock::time_point start = high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        double amount = 100 + (i % 500);

        if (i % 100 < percentage)
            amount = -amount;

        if (!validateReturnCode(amount))
            errors++;
    }

    high_resolution_clock::time_point stop = high_resolution_clock::now();

    resultValue = errors;

    return duration<double, milli>(stop - start).count();
}

double exceptionBenchmark(int n, int percentage)
{
    int errors = 0;

    high_resolution_clock::time_point start = high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        double amount = 100 + (i % 500);

        if (i % 100 < percentage)
            amount = -amount;

        try
        {
            validateException(amount);
        }
        catch (const exception&)
        {
            errors++;
        }
    }

    high_resolution_clock::time_point stop = high_resolution_clock::now();

    resultValue = errors;

    return duration<double, milli>(stop - start).count();
}

void correctnessTest()
{
    double virtualSum = 0;
    double switchSum = 0;

    cout << "\nB3.1 CORRECTNESS TEST\n";
    cout << "Bill\tVirtual\tSwitch\n";

    for (int i = 0; i < 10; i++)
    {
        BillData b = makeBill(i);
        double v;

        if (b.type == 0)
        {
            OutPatientBill bill(b.a, b.b, b.fee);
            v = bill.total();
        }
        else if (b.type == 1)
        {
            InPatientBill bill(b.a, b.b, b.fee);
            v = bill.total();
        }
        else
        {
            TelephoneBill bill(b.a, b.b, b.fee);
            v = bill.total();
        }

        double s = switchTotal(b);

        virtualSum += v;
        switchSum += s;

        cout << i + 1 << "\t" << v << "\t" << s << endl;
    }

    cout << "Virtual Total: " << virtualSum << endl;
    cout << "Switch Total: " << switchSum << endl;

    if (virtualSum == switchSum)
        cout << "Both methods give the same result.\n";
    else
        cout << "Results do not match.\n";
}

void performanceTest()
{
    int sizes[] = {1000, 1000000, 10000000};

    cout << "\nB3.2 VIRTUAL FUNCTIONS VS SWITCH\n";
    cout << "Bills\t\tVirtual(ms)\tSwitch(ms)\n";

    for (int i = 0; i < 3; i++)
    {
        int n = sizes[i];

        double v = virtualBenchmark(n);
        double s = switchBenchmark(n);

        cout << n << "\t\t" << v << "\t\t" << s << endl;
    }
}

void exceptionTest()
{
    int n = 1000000;
    int percentages[] = {0, 1, 50};

    cout << "\nB3.3 RETURN CODES VS EXCEPTIONS\n";
    cout << "Invalid%\tReturn(ms)\tException(ms)\n";

    for (int i = 0; i < 3; i++)
    {
        int p = percentages[i];

        double r = returnCodeBenchmark(n, p);
        double e = exceptionBenchmark(n, p);

        cout << p << "%\t\t" << r << "\t\t" << e << endl;
    }
}

int main()
{
    cout << fixed << setprecision(3);

    correctnessTest();
    performanceTest();
    exceptionTest();

    cout << "\nAll tests completed.\n";

    return 0;
}
