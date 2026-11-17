
#include <iostream>
#include <string>
using namespace std;

class Time
{
    int hours, minutes, seconds;

public:

    Time(int h = 0, int m = 0, int s = 0)
    {
        int total = h * 3600 + m * 60 + s;

        hours = (total / 3600) % 24;
        minutes = (total / 60) % 60;
        seconds = total % 60;
    }

    Time& operator++()
    {
        seconds++;

        if (seconds == 60)
        {
            seconds = 0;
            minutes++;
        }

        if (minutes == 60)
        {
            minutes = 0;
            hours++;
        }

        if (hours == 24)
        {
            hours = 0;
        }

        return *this;
    }

    Time operator++(int)
    {
        Time old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Time& t) const
    {
        return hours == t.hours &&
               minutes == t.minutes &&
               seconds == t.seconds;
    }

    bool operator<(const Time& t) const
    {
        if (hours != t.hours)
            return hours < t.hours;

        if (minutes != t.minutes)
            return minutes < t.minutes;

        return seconds < t.seconds;
    }

    void display() const
    {
        cout << hours << ":"
             << (minutes < 10 ? "0" : "") << minutes << ":"
             << (seconds < 10 ? "0" : "") << seconds << endl;
    }
};

class Playlist
{
    string tracks[3];
    int size;

public:

    Playlist()
    {
        tracks[0] = "Song 1";
        tracks[1] = "Song 2";
        tracks[2] = "Song 3";
        size = 3;
    }

    string& operator[](int i)
    {
        if (i < 0 || i >= size)
        {
            throw out_of_range("Invalid playlist index");
        }

        return tracks[i];
    }

    const string& operator[](int i) const
    {
        if (i < 0 || i >= size)
        {
            throw out_of_range("Invalid playlist index");
        }

        return tracks[i];
    }
};

int main()
{
    try
    {
        Time t(0, 0, 5);

        Time a = t++;
        Time b = ++t;

        cout << "Postfix value: ";
        a.display();

        cout << "Prefix value: ";
        b.display();

        cout << "Current time: ";
        t.display();

        Time x(0, 59, 59);

        cout << "Before increment: ";
        x.display();

        ++x;

        cout << "After increment: ";
        x.display();

        Time p(1, 0, 0);
        Time q(2, 0, 0);

        cout << "Time equal: " << boolalpha << (p == q) << endl;
        cout << "Time less: " << (p < q) << endl;

        Playlist playlist;

        cout << "\nPlaylist:" << endl;

        for (int i = 0; i < 3; i++)
        {
            cout << playlist[i] << endl;
        }

        playlist[1] = "New Song";

        cout << "\nUpdated Track: " << playlist[1] << endl;

        cout << "\nInvalid Index Test:" << endl;

        cout << playlist[-1] << endl;
    }
    catch (const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
