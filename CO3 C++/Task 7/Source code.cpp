
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Complex
{
    double real, imag;

public:

    Complex() : real(0), imag(0)
    {
    }

    Complex(double r) : real(r), imag(0)
    {
    }

    Complex(double r, double i) : real(r), imag(i)
    {
    }

    Complex operator+(const Complex& c) const
    {
        return Complex(real + c.real, imag + c.imag);
    }

    Complex operator-(const Complex& c) const
    {
        return Complex(real - c.real, imag - c.imag);
    }

    Complex operator*(const Complex& c) const
    {
        return Complex(
            real * c.real - imag * c.imag,
            real * c.imag + imag * c.real
        );
    }

    Complex operator/(const Complex& c) const
    {
        double denominator = c.real * c.real + c.imag * c.imag;

        if (denominator == 0)
        {
            throw runtime_error("Division by zero impedance");
        }

        return Complex(
            (real * c.real + imag * c.imag) / denominator,
            (imag * c.real - real * c.imag) / denominator
        );
    }

    bool operator==(const Complex& c) const
    {
        return real == c.real && imag == c.imag;
    }

    double magnitude() const
    {
        return sqrt(real * real + imag * imag);
    }

    friend ostream& operator<<(ostream& out, const Complex& c)
    {
        out << c.real;

        if (c.imag >= 0)
            out << " + " << c.imag << "j";
        else
            out << " - " << -c.imag << "j";

        return out;
    }
};

int main()
{
    try
    {
        Complex R(10, 0);
        Complex L(0, 5);
        Complex C(0, -3);

        cout << "Resistor: " << R << endl;
        cout << "Inductor: " << L << endl;
        cout << "Capacitor: " << C << endl;

        Complex series = R + L + C;

        cout << "\nSeries Impedance: " << series << endl;
        cout << "Series Magnitude: " << series.magnitude() << endl;

        Complex parallel = (R * L) / (R + L);

        cout << "\nParallel Impedance: " << parallel << endl;
        cout << "Parallel Magnitude: " << parallel.magnitude() << endl;

        Complex a(5, 3);
        Complex b(2, 1);

        cout << "\nAddition: " << a + b << endl;
        cout << "Subtraction: " << a - b << endl;
        cout << "Multiplication: " << a * b << endl;
        cout << "Division: " << a / b << endl;

        cout << "Equality: " << boolalpha << (a == b) << endl;

        Complex zero(0, 0);

        cout << "\nDivision by zero test:" << endl;
        Complex result = a / zero;

        cout << result << endl;
    }
    catch (const runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
