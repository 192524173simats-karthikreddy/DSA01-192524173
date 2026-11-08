#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
const int CAPACITY = 10;
class OriginalBuffer {
private:
    double transactions[CAPACITY];
    int count;
public:
    OriginalBuffer() {
        count = 0;
    }
    void addTransaction(double amount) {
        if (count < CAPACITY) {
            transactions[count] = amount;
            count++;
        } else {
            // Shift all elements to the left
            for (int i = 0; i < CAPACITY - 1; i++) {
                transactions[i] = transactions[i + 1];
            }
            transactions[CAPACITY - 1] = amount;
        }
    }
    void display() const {
        for (int i = 0; i < count; i++) {
            cout << transactions[i] << " ";
        }
        cout << '\n';
    }
    double total() const {
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum += transactions[i];
        }
        return sum;
    }
};
class CircularBuffer {
private:
    double transactions[CAPACITY];
    int count;
    int next;
public:
    CircularBuffer() {
        count = 0;
        next = 0;
    }
    void addTransaction(double amount) {
        transactions[next] = amount;
        next = (next + 1) % CAPACITY;
        if (count < CAPACITY) {
            count++;
        }
    }
    void display() const {
        int start;
        if (count == CAPACITY) {
            start = next;
        } else {
            start = 0;
        }
        for (int i = 0; i < count; i++) {
            int index = (start + i) % CAPACITY;
            cout << transactions[index] << " ";
        }
        cout << '\n';
    }
    double total() const {
        double sum = 0;
        int start;
        if (count == CAPACITY) {
            start = next;
        } else {
            start = 0;
        }
        for (int i = 0; i < count; i++) {
            int index = (start + i) % CAPACITY;
            sum += transactions[index];
        }
        return sum;
    }
};
long long testOriginal(int numberOfTransactions) {
    OriginalBuffer original;
    auto start = steady_clock::now();
    for (int i = 1; i <= numberOfTransactions; i++) {
        original.addTransaction(i % 1000);
    }
    auto stop = steady_clock::now();
    cout << "Original final transactions: ";
    original.display();
    cout << "Original total: " << original.total() << '\n';
    return duration_cast<milliseconds>(stop - start).count();
}
long long testCircular(int numberOfTransactions) {
    CircularBuffer circular;
    auto start = steady_clock::now();
    for (int i = 1; i <= numberOfTransactions; i++) {
        circular.addTransaction(i % 1000);
    }
    auto stop = steady_clock::now();
    cout << "Circular final transactions: ";
    circular.display();
    cout << "Circular total: " << circular.total() << '\n';
    return duration_cast<milliseconds>(stop - start).count();
}
int main() {
    cout << "===== Q7: ORIGINAL VS REDESIGNED =====\n";
    OriginalBuffer original;
    CircularBuffer circular;
    for (int i = 100; i <= 1200; i += 100) {
        original.addTransaction(i);
        circular.addTransaction(i);
    }
    cout << "\nOriginal transactions: ";
    original.display();
    cout << "Circular transactions: ";
    circular.display();
    cout << "\nOriginal total: " << original.total() << '\n';
    cout << "Circular total: " << circular.total() << '\n';
    const int TEST_SIZE = 2000000;
    cout << "\n===== PERFORMANCE TEST =====\n";
    cout << "Number of insertions: " << TEST_SIZE << '\n';
    cout << "Array capacity: " << CAPACITY << '\n';
    long long originalTime = testOriginal(TEST_SIZE);
    long long circularTime = testCircular(TEST_SIZE);
    cout << "\nOriginal time: "
         << originalTime << " ms\n";
    cout << "Circular buffer time: "
         << circularTime << " ms\n";
    return 0;
}
