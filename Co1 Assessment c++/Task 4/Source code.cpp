#include <iostream>
using namespace std;
class SavingsAccount
{
private:
    int accountNumber;
    double balance;
    double transactions[10];
    int count;
public:
    SavingsAccount(int accNo, double initialBalance)
    {
        accountNumber = accNo;
        balance = initialBalance;
        count = 0;
    }
    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid deposit amount!" << endl;
            return;
        }
        balance += amount;
        addTransaction(amount);
        cout << "Deposited: Rs. " << amount << endl;
    }
    void withdraw(double amount);
    void miniStatement();
    void addTransaction(double amount)
    {
        if (count < 10)
        {
            transactions[count] = amount;
            count++;
        }
        else
        {
            for (int i = 0; i < 9; i++)
            {
                transactions[i] = transactions[i + 1];
            }
            transactions[9] = amount;
        }
    }
};
void SavingsAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        cout << "Invalid withdrawal amount!" << endl;
        return;
    }
    if (amount > balance)
    {
        cout << "Insufficient balance!" << endl;
        return;
    }
    balance -= amount;
    addTransaction(-amount);

    cout << "Withdrawn: Rs. " << amount << endl;
}
void SavingsAccount::miniStatement()
{
    cout << "\n===== MINI STATEMENT =====" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Current Balance: Rs. " << balance << endl;
    cout << "\nLast " << count << " Transactions:" << endl;
    for (int i = 0; i < count; i++)
    {
        if (transactions[i] > 0)
        {
            cout << "Deposit: Rs. " << transactions[i] << endl;
        }
        else
        {
            cout << "Withdrawal: Rs. " << -transactions[i] << endl;
        }
    }
    cout << "==========================" << endl;
}
int main()
{
    SavingsAccount account(1001, 5000);
    account.deposit(1000);
    account.withdraw(500);
    account.deposit(2000);
    account.withdraw(300);
    account.deposit(1500);
    account.withdraw(200);
    account.miniStatement();
    return 0;
}
