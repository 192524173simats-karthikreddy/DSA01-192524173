#include <iostream>
using namespace std;
void applyByValue(long long fee, int percent)
{
    fee = fee - (fee * percent / 100);
    cout << "Inside Call by Value: " << fee << endl;
}
void applyByReference(long long &fee, int percent)
{
    fee = fee - (fee * percent / 100);
    cout << "Inside Call by Reference: " << fee << endl;
}
void applyByPointer(long long *fee, int percent)
{
    *fee = *fee - (*fee * percent / 100);
    cout << "Inside Call by Pointer: " << *fee << endl;
}
void change(int a, int& b, int* c)
{
    a += 10;
    b += 10;
    *c += 10;
}
int& bigger(int& p, int& q)
{
    return p > q ? p : q;
}
void show(int x, int y = 5, int z = 10)
{
    cout << x + y + z << ' ';
}
void applyConcession(long long& fee, int percent)
{
    fee -= fee * percent / 100;
}
long long applyConcessionReturn(long long fee, int percent)
{
    return fee - (fee * percent / 100);
}
int main()
{
    cout << "===== PART 1: CONCESSION METHODS =====" << endl;
    long long fee1 = 45000;
    long long fee2 = 45000;
    long long fee3 = 45000;
    cout << "Original Hostel Fee: 45000" << endl;
    applyByValue(fee1, 10);
    cout << "Stored Fee after Value: " << fee1 << endl;
    applyByReference(fee2, 10);
    cout << "Stored Fee after Reference: " << fee2 << endl;
    applyByPointer(&fee3, 10);
    cout << "Stored Fee after Pointer: " << fee3 << endl;
    cout << "\n===== PART 2: PREDICT THE OUTPUT =====" << endl;
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    cout << a << ' ' << b << ' ' << c << endl;
    bigger(a, c) = 100;
    cout << a << ' ' << c << endl;
    show(1);
    show(1, 2);
    show(1, 2, 3);
    cout << endl;
    cout << "\n===== PART 3: TODO COMPLETION =====" << endl;
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    cout << "after call by value : " << hostelFee << endl;
    applyConcession(hostelFee, 10);
    cout << "after call by reference: " << hostelFee << endl;
    cout << "\n===== PART 4: RETURN METHOD =====" << endl;
    long long newFee = 45000;
    newFee = applyConcessionReturn(newFee, 10);
    cout << "Updated Hostel Fee: " << newFee << endl;
    return 0;
}
