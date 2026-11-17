
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <new>
using namespace std;

// Base exception class
class BillingError : public runtime_error
{
public:
    BillingError(string message) : runtime_error(message) {}
};

// Negative charge exception
class NegativeChargeError : public BillingError
{
public:
    NegativeChargeError()
        : BillingError("Bill amount cannot be negative.") {}
};

// Claim exception
class ClaimError : public BillingError
{
public:
    ClaimError()
        : BillingError("Claim amount exceeds cover limit.") {}
};

// Unknown package exception
class UnknownPackageError : public BillingError
{
public:
    UnknownPackageError()
        : BillingError("Unknown government package.") {}
};

// Patient not found exception
class PatientNotFoundError : public BillingError
{
public:
    PatientNotFoundError()
        : BillingError("Patient record not found.") {}
};

// Bill class
class Bill
{
    double amount;

public:
    Bill(double a)
    {
        if (a < 0)
            throw NegativeChargeError();

        amount = a;
    }

    double getAmount() const noexcept
    {
        return amount;
    }

    ~Bill() noexcept {}
};

// Validate insurance claim
void validateClaim(double claim, double coverLimit)
{
    if (claim > coverLimit)
        throw ClaimError();

    cout << "Claim approved: Rs. " << claim << endl;
}

// Get government package rate
double getPackageRate(string package)
{
    if (package == "GOLD")
        return 5000;

    if (package == "SILVER")
        return 3000;

    throw UnknownPackageError();
}

// Find patient record
string findPatient(int id)
{
    vector<int> patientIDs = {101, 102, 103};

    for (int i = 0; i < patientIDs.size(); i++)
    {
        if (patientIDs[i] == id)
            return "Patient Found";
    }

    throw PatientNotFoundError();
}

// Allocate memory
unique_ptr<int[]> allocateMemory(int size)
{
    return unique_ptr<int[]>(new int[size]);
}

int main()
{
    cout << "===== EXCEPTION HANDLING =====" << endl;

    // 1. Negative charge
    try
    {
        Bill b(-500);
    }
    catch (const NegativeChargeError& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    // 2. Claim above cover limit
    try
    {
        validateClaim(9000, 8000);
    }
    catch (const ClaimError& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    // 3. Unknown package
    try
    {
        double rate = getPackageRate("PLATINUM");
        cout << "Package Rate: Rs. " << rate << endl;
    }
    catch (const UnknownPackageError& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    // 4. Missing patient record
    try
    {
        cout << findPatient(999) << endl;
    }
    catch (const PatientNotFoundError& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    // 5. Memory allocation
    try
    {
        unique_ptr<int[]> memory = allocateMemory(10);

        cout << "Memory allocated successfully." << endl;
    }
    catch (const bad_alloc& e)
    {
        cout << "Error: Memory allocation failed." << endl;
    }

    // Successful bill
    try
    {
        Bill b(2500);

        cout << "Valid Bill Amount: Rs. "
             << b.getAmount() << endl;
    }
    catch (const BillingError& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
