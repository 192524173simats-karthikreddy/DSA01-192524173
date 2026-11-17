
#include <iostream>
#include <string>
using namespace std;

class Prescription
{
    int n;
    string* medicines;

public:

    explicit Prescription(int count) : n(count), medicines(new string[count])
    {
    }

    Prescription(const Prescription& p) : n(p.n), medicines(new string[p.n])
    {
        cout << "Copy constructor called" << endl;

        for (int i = 0; i < n; i++)
        {
            medicines[i] = p.medicines[i];
        }
    }

    Prescription& operator=(const Prescription& p)
    {
        if (this != &p)
        {
            string* temp = new string[p.n];

            for (int i = 0; i < p.n; i++)
            {
                temp[i] = p.medicines[i];
            }

            delete[] medicines;

            medicines = temp;
            n = p.n;
        }

        return *this;
    }

    ~Prescription()
    {
        delete[] medicines;
    }

    void set(int i, const string& m)
    {
        medicines[i] = m;
    }

    string get(int i) const
    {
        return medicines[i];
    }

    void display() const
    {
        for (int i = 0; i < n; i++)
        {
            cout << medicines[i] << " ";
        }
        cout << endl;
    }
};

void passByValue(Prescription p)
{
    cout << "Passed by value" << endl;
}

void passByReference(const Prescription& p)
{
    cout << "Passed by const reference" << endl;
}

int main()
{
    Prescription p(2);

    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;

    q.set(1, "Cetirizine");

    Prescription r(1);

    r = p;

    p.set(0, "Ibuprofen");

    cout << p.get(0) << " " << p.get(1) << " | ";
    cout << q.get(0) << " " << q.get(1) << " | ";
    cout << r.get(0) << " " << r.get(1) << endl;

    p = p;

    passByValue(p);
    passByReference(p);

    return 0;
}
