#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
class Time {
private:
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
    int getHours() const {
        return h;
    }
    int getMinutes() const {
        return m;
    }
    int minutesTo(const Time& b) const;
    bool isEarlier(const Time& b) const;
};
inline int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    int difference = first - second;
    if (difference < 0) {
        difference = -difference;
    }
    return difference;
}
inline bool earlier(const Time& a, const Time& b) {
    if (a.h < b.h) {
        return true;
    }
    if (a.h == b.h && a.m < b.m) {
        return true;
    }
    return false;
}
int Time::minutesTo(const Time& b) const {
    int first = h * 60 + m;
    int second = b.h * 60 + b.m;
    int difference = first - second;
    if (difference < 0) {
        difference = -difference;
    }
    return difference;
}
bool Time::isEarlier(const Time& b) const {
    if (h < b.h) {
        return true;
    }
    if (h == b.h && m < b.m) {
        return true;
    }
    return false;
}
int getterMinutesBetween(const Time& a, const Time& b) {
    int first = a.getHours() * 60 + a.getMinutes();
    int second = b.getHours() * 60 + b.getMinutes();
    int difference = first - second;
    if (difference < 0) {
        difference = -difference;
    }
    return difference;
}
bool getterEarlier(const Time& a, const Time& b) {
    if (a.getHours() < b.getHours()) {
        return true;
    }
    if (a.getHours() == b.getHours() &&
        a.getMinutes() < b.getMinutes()) {
        return true;
    }
    return false;
}
#if defined(__GNUC__)
__attribute__((noinline))
#endif
int normalMinutesBetween(const Time& a, const Time& b) {
    return getterMinutesBetween(a, b);
}
#if defined(__GNUC__)
__attribute__((noinline))
#endif
bool normalEarlier(const Time& a, const Time& b) {
    return getterEarlier(a, b);
}
template <typename Function>
void measureTime(const char* label, Function function,
                 const Time& a, const Time& b) {
    const int repetitions = 10000000;
    long long result = 0;
    auto start = steady_clock::now();
    for (int i = 0; i < repetitions; i++) {
        result += function(a, b);
    }
    auto stop = steady_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << label << ": " << duration.count()
         << " ms | Result: " << result << '\n';
}
int main() {
    cout << "===== FRIEND FUNCTION TEST =====\n";
    Time departure(9, 45);
    Time arrival(13, 10);
    cout << minutesBetween(departure, arrival) << " "
         << boolalpha << earlier(arrival, departure) << '\n';
    cout << "\n===== CORRECTNESS TESTS =====\n";
    Time t1(12, 30);
    Time t2(12, 30);
    cout << "Same time difference: "
         << minutesBetween(t1, t2) << '\n';
    cout << "Same time earlier: "
         << earlier(t1, t2) << '\n';
    Time morning(11, 30);
    Time afternoon(12, 30);
    cout << "Before noon to after noon: "
         << minutesBetween(morning, afternoon) << '\n';
    cout << "Morning earlier than afternoon: "
         << earlier(morning, afternoon) << '\n';
    cout << "\n===== MEMBER FUNCTION TEST =====\n";
    cout << "Minutes between: "
         << departure.minutesTo(arrival) << '\n';
    cout << "Departure earlier than arrival: "
         << departure.isEarlier(arrival) << '\n';
    cout << "\n===== GETTER FUNCTION TEST =====\n";
    cout << "Minutes between: "
         << getterMinutesBetween(departure, arrival) << '\n';
    cout << "Departure earlier than arrival: "
         << getterEarlier(departure, arrival) << '\n';
    cout << "\n===== 10 MILLION CALL BENCHMARK =====\n";
    measureTime("Inline friend minutesBetween",
                minutesBetween, departure, arrival);
    measureTime("Non-inline minutesBetween",
                normalMinutesBetween, departure, arrival);
    measureTime("Inline friend earlier",
                earlier, departure, arrival);
    measureTime("Non-inline earlier",
                normalEarlier, departure, arrival);
    return 0;
}
