
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <new>
using namespace std;

class ClaimError : public runtime_error
{
public:
    using runtime_error::runtime_error;
};

class Guard
{
    string name;

public:
    Guard(string n) : name(n)
    {
        cout << name << " created" << endl;
    }

    ~Guard() noexcept
    {
        cout << name << " destroyed" << endl;
    }
};

void validateBill(double amount)
{
    if (amount < 0)
        throw invalid_argument("Negative bill amount");
}

void approve(double billed, double cover)
{
    if (billed < 0 || cover < 0)
        throw invalid_argument("Negative claim amount");

    if (billed > cover)
        throw ClaimError("Claim exceeds cover limit");

    cout << "Claim approved" << endl;
}

double getPackageRate(string package)
{
    if (package == "GOLD")
        return 5000;

    if (package == "SILVER")
        return 3000;

    throw runtime_error("Unknown package code");
}

double convertNumber(string text)
{
    return stod(text);
}

void allocateMemory()
{
    size_t size = numeric_limits<size_t>::max();
    int* p = new int[size];
    delete[] p;
}

template <class Function>
void runTest(string testName, Function test)
{
    cout << "\n" << testName << endl;

    try
    {
        test();
    }
    catch (const bad_alloc&)
    {
        cout << "Caught: Memory allocation failed" << endl;
    }
    catch (const exception& e)
    {
        cout << "Caught: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Caught: Unknown exception" << endl;
    }
}

int main()
{
    cout << "===== BILLING ERROR TESTS =====" << endl;

    runTest("TEST 1: NEGATIVE BILL", []()
    {
        Guard g("Bill Object");
        validateBill(-500);
    });

    runTest("TEST 2: CLAIM ABOVE COVER", []()
    {
        Guard g("Claim Object");
        approve(60000, 50000);
    });

    runTest("TEST 3: UNKNOWN PACKAGE", []()
    {
        Guard g("Package Object");
        double rate = getPackageRate("PLATINUM");
        cout << "Package Rate: " << rate << endl;
    });

    runTest("TEST 4: INVALID NUMBER", []()
    {
        Guard g("Conversion Object");
        double amount = convertNumber("hello");
        cout << "Amount: " << amount << endl;
    });

    runTest("TEST 5: MEMORY ALLOCATION", []()
    {
        Guard g("Memory Object");
        allocateMemory();
        cout << "Memory allocated successfully" << endl;
    });

    runTest("TEST 6: UNKNOWN EXCEPTION", []()
    {
        Guard g("Unknown Object");
        throw 100;
    });

    cout << "\nProgram continues after all errors." << endl;

    return 0;
}
