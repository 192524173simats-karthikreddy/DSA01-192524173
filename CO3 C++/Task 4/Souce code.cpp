
#include <iomanip>
#include <iostream>
using namespace std;

class Money
{
    long long paise;

public:

    Money(long long rupees = 0, int p = 0)
        : paise(rupees * 100 + p)
    {
    }

    Money operator+(const Money& m) const
    {
        return Money(0, paise + m.paise);
    }

    Money operator-(const Money& m) const
    {
        return Money(0, paise - m.paise);
    }

    Money& operator+=(const Money& m)
    {
        paise += m.paise;
        return *this;
    }

    bool operator==(const Money& m) const
    {
        return paise == m.paise;
    }

    bool operator<(const Money& m) const
    {
        return paise < m.paise;
    }

    friend ostream& operator<<(ostream& out, const Money& m)
    {
        long long value = m.paise;

        if (value < 0)
        {
            out << "-Rs " << -value / 100 << "."
                << setw(2) << setfill('0') << -value % 100;
        }
        else
        {
            out << "Rs " << value / 100 << "."
                << setw(2) << setfill('0') << value % 100;
        }

        return out;
    }

    friend istream& operator>>(istream& in, Money& m)
    {
        long long r;
        int p;

        cout << "Enter rupees and paise: ";

        if (in >> r >> p)
        {
            if (p < 0 || p > 99)
            {
                in.setstate(ios::failbit);
            }
            else
            {
                m.paise = r * 100 + p;
            }
        }

        return in;
    }
};

int main()
{
    Money a(120, 75), b(79, 25);

    Money c = a + b;

    cout << "Addition: " << c << endl;

    cout << boolalpha << (c == Money(200)) << endl;

    Money x(0, 75), y(0, 50);

    cout << "Paise Carry: " << x + y << endl;

    Money d(50, 0), e(80, 0);

    cout << "Subtraction: " << d - e << endl;

    d += e;

    cout << "After += : " << d << endl;

    cout << "Comparison: " << boolalpha << (d < e) << endl;

    return 0;
}
