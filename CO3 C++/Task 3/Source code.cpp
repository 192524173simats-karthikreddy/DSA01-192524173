
#include <iostream>
using namespace std;

class Auditorium
{
    int rows, seats;
    char** seatMap;
    int booked;

public:

    Auditorium(int r, int s) : rows(r), seats(s), booked(0), seatMap(nullptr)
    {
        cout << "Constructor called" << endl;

        if (rows > 0 && seats > 0)
        {
            seatMap = new char*[rows];

            for (int i = 0; i < rows; i++)
            {
                seatMap[i] = new char[seats];

                for (int j = 0; j < seats; j++)
                {
                    seatMap[i][j] = 'O';
                }
            }
        }
    }

    void bookSeat(int r, int s)
    {
        if (r >= 0 && r < rows && s >= 0 && s < seats)
        {
            if (seatMap[r][s] == 'O')
            {
                seatMap[r][s] = 'X';
                booked++;
                cout << "Seat booked" << endl;
            }
            else
            {
                cout << "Seat already booked" << endl;
            }
        }
        else
        {
            cout << "Invalid seat" << endl;
        }
    }

    void cancelSeat(int r, int s)
    {
        if (r >= 0 && r < rows && s >= 0 && s < seats)
        {
            if (seatMap[r][s] == 'X')
            {
                seatMap[r][s] = 'O';
                booked--;
                cout << "Booking cancelled" << endl;
            }
            else
            {
                cout << "Seat is not booked" << endl;
            }
        }
        else
        {
            cout << "Invalid seat" << endl;
        }
    }

    void display()
    {
        cout << "\nSeat Map:" << endl;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < seats; j++)
            {
                cout << seatMap[i][j] << " ";
            }
            cout << endl;
        }
    }

    ~Auditorium()
    {
        if (seatMap != nullptr)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] seatMap[i];
            }

            delete[] seatMap;
        }

        cout << "Destructor called" << endl;
        cout << "Total booked seats: " << booked << endl;
        cout << "Memory released" << endl;
    }
};

int main()
{
    cout << "Stack Object:" << endl;

    Auditorium a1(2, 3);
    a1.bookSeat(0, 1);
    a1.bookSeat(1, 2);
    a1.display();

    cout << "\nBlock Object:" << endl;

    {
        Auditorium a2(2, 2);
        a2.bookSeat(0, 0);
        a2.display();
    }

    cout << "\nHeap Object:" << endl;

    Auditorium* a3 = new Auditorium(3, 3);
    a3->bookSeat(1, 1);
    a3->cancelSeat(1, 1);
    a3->display();

    delete a3;

    cout << "\nZero Row Object:" << endl;

    Auditorium a4(0, 3);

    cout << "\nEnd of Program" << endl;

    return 0;
}
