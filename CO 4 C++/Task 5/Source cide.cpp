
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Cart
{
    string items[10];
    double prices[10];
    int n = 0;
    double discount = 0;

public:

    // TODO 1: Add item and return *this
    Cart& add(string item, double price)
    {
        if (n < 10)
        {
            items[n] = item;
            prices[n] = price;
            n++;
        }

        return *this;
    }

    // TODO 2: Set discount using this pointer
    Cart& setDiscount(double discount)
    {
        this->discount = discount;
        return *this;
    }

    double total() const
    {
        double t = 0;

        for (int i = 0; i < n; i++)
        {
            t += prices[i];
        }

        return t * (100 - discount) / 100;
    }

    void display() const
    {
        cout << "Cart Total: " << total() << endl;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    // (a) Direct access using object name
    cout << "1. DIRECT OBJECT" << endl;

    Cart c1;
    c1.add("Rice", 60).add("Dal", 120).setDiscount(10);
    c1.display();

    // (b) Access using pointer and ->
    cout << "\n2. POINTER ACCESS" << endl;

    Cart* p = &c1;
    p->add("Oil", 180);
    p->display();

    // (c) Access using reference
    cout << "\n3. REFERENCE ACCESS" << endl;

    Cart& r = c1;
    r.add("Sugar", 40);
    r.display();

    // (d) Dynamic object using new and delete
    cout << "\n4. DYNAMIC OBJECT" << endl;

    Cart* p2 = new Cart;
    p2->add("Milk", 50).add("Bread", 30);
    p2->display();

    delete p2;
    p2 = nullptr;

    // Task 5.2: Array of pointers to Cart objects
    cout << "\n5. ARRAY OF CART POINTERS" << endl;

    Cart a, b, d;

    a.add("Rice", 100).add("Oil", 200);
    b.add("Milk", 150).add("Bread", 100);
    d.add("Sugar", 300).add("Dal", 200);

    Cart* carts[3] = {&a, &b, &d};

    Cart* highest = carts[0];

    for (int i = 1; i < 3; i++)
    {
        if (carts[i]->total() > highest->total())
        {
            highest = carts[i];
        }
    }

    cout << "Highest Cart Total: " << highest->total() << endl;

    // Alternative: Using vector<Cart>
    cout << "\n6. VECTOR OF CART OBJECTS" << endl;

    vector<Cart> cartList(3);

    cartList[0].add("Rice", 100).add("Oil", 200);
    cartList[1].add("Milk", 150).add("Bread", 100);
    cartList[2].add("Sugar", 300).add("Dal", 200);

    int maxIndex = 0;

    for (int i = 1; i < cartList.size(); i++)
    {
        if (cartList[i].total() > cartList[maxIndex].total())
        {
            maxIndex = i;
        }
    }

    cout << "Highest Vector Cart Total: "
         << cartList[maxIndex].total() << endl;

    return 0;
}
