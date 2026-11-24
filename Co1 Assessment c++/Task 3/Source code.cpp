#include <iostream>
using namespace std;
struct Parcel
{
    double weight;
    bool express;
    bool insured;
};
double charge(int grams)
{
    cout << "Selected: Integer (grams) function" << endl;
    return 30 + (grams * 0.05);
}
double charge(double weight, bool express = false, bool insured = false)
{
    cout << "Selected: Double (kg) function" << endl;
    double amount = 50 + (weight * 20);
    if (express)
    {
        amount += 30;
    }
    if (insured)
    {
        amount += 10;
    }
    return amount;
}
double charge(const Parcel& p)
{
    cout << "Selected: Parcel object function" << endl;
    double amount = 50 + (p.weight * 20);
    if (p.express)
    {
        amount += 30;
    }
    if (p.insured)
    {
        amount += 10;
    }
    return amount;
}
int main()
{
    cout << "===== COURIER CHARGE CALCULATOR =====" << endl;
    Parcel p = {3.0, true, true};
    cout << "\nCall 1: charge(2)" << endl;
    cout << "Charge: Rs. " << charge(2) << endl;
    cout << "\nCall 2: charge(2.0f)" << endl;
    cout << "Charge: Rs. " << charge(2.0f) << endl;
    cout << "\nCall 3: charge(500)" << endl;
    cout << "Charge: Rs. " << charge(500) << endl;
    cout << "\nCall 4: charge(1.5)" << endl;
    cout << "Charge: Rs. " << charge(1.5) << endl;
    cout << "\nCall 5: charge(1.5, true)" << endl;
    cout << "Charge: Rs. " << charge(1.5, true) << endl;
    cout << "\nCall 6: charge(p)" << endl;
    cout << "Charge: Rs. " << charge(p) << endl;
    return 0;
}
