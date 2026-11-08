#include <iostream>
#include <string>
using namespace std;
class BusTicket {
private:
    static int issued;
    static const int CAPACITY = 3;

    int seat;
    string name;
public:
    explicit BusTicket(const string& n) : seat(0), name(n) {
        if (issued < CAPACITY) {
            issued++;
            seat = issued;
        }
    }
    static int count() {
        // TODO 2: Return the number of seats issued
        return issued;
    }
    void print() const {
        cout << name << ": "
             << (seat ? "Seat " + to_string(seat) : string("Waiting"))
             << '\n';
    }
};
int BusTicket::issued = 0;
void createTickets() {
    BusTicket tickets[2] = {
        BusTicket("Ravi"),
        BusTicket("Sita")
    };
    for (const BusTicket& t : tickets) {
        t.print();
    }
    cout << "Issued: " << BusTicket::count() << "\n\n";
}
int main() {
    cout << "===== BUS TICKET ALLOCATION =====\n";
    BusTicket trip[4] = {
        BusTicket("Asha"),
        BusTicket("Bala"),
        BusTicket("Chitra"),
        BusTicket("Dev")
    };
    for (const BusTicket& t : trip) {
        t.print();
    }
    cout << "Issued: " << BusTicket::count() << "\n\n";
    cout << "===== TICKETS CREATED INSIDE A FUNCTION =====\n";
    cout << "First function call:\n";
    createTickets();
    cout << "Second function call:\n";
    createTickets();
    return 0;
}
