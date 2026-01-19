#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Transaction class
class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d)
        : type(t), amount(a), details(d) {}
};

// Account class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo, double initialBalance = 0.0)
        : accountNumber(accNo), balance(initialBalance) {}

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount, "Successful");
        cout << "Deposited " << amount << " successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Error: Insufficient funds.\n";
            transactions.emplace_back("Withdraw", amount, "Failed - Insufficient funds");
        } else {
            balance -= amount;
            transactions.emplace_back("Withdraw", amount, "Successful");
            cout << "Withdrew " << amount << " successfully.\n";
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount > balance) {
            cout << "Error: Insufficient funds for transfer.\n";
            transactions.emplace_back("Transfer", amount, "Failed - Insufficient funds");
        } else {
            balance -= amount;
            toAccount.balance += amount;
            transactions.emplace_back("Transfer", amount, "To Account " + to_string(toAccount.getAccountNumber()));
            toAccount.transactions.emplace_back("Transfer", amount, "From Account " + to_string(accountNumber));
            cout << "Transferred " << amount << " to Account " << toAccount.getAccountNumber() << " successfully.\n";
        }
    }

    void showTransactions() const {
        cout << "\nTransaction History for Account " << accountNumber << ":\n";
        cout << left << setw(15) << "Type" << setw(10) << "Amount" << setw(30) << "Details\n";
        cout << "-------------------------------------------------------------\n";
        for (const auto &t : transactions) {
            cout << left << setw(15) << t.type
                 << setw(10) << t.amount
                 << setw(30) << t.details << "\n";
        }
    }

    void showAccountInfo() const {
        cout << "\nAccount Number: " << accountNumber << "\n";
        cout << "Balance: " << balance << "\n";
    }
};

// Customer class
class Customer {
private:
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(string n, int id) : name(n), customerID(id) {}

    string getName() const { return name; }
    int getCustomerID() const { return customerID; }

    void createAccount(int accNo, double initialBalance = 0.0) {
        accounts.emplace_back(accNo, initialBalance);
        cout << "Account " << accNo << " created successfully for " << name << ".\n";
    }

    Account* getAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNo) return &acc;
        }
        return nullptr;
    }

    void showCustomerInfo() const {
        cout << "\nCustomer ID: " << customerID << "\n";
        cout << "Name: " << name << "\n";
        cout << "Accounts:\n";
        for (const auto &acc : accounts) {
            acc.showAccountInfo();
        }
    }
};

// Main Banking System
int main() {
    vector<Customer> customers;
    int choice;

    cout << "======================================" << endl;
    cout << "        BANKING SYSTEM MENU           " << endl;
    cout << "======================================" << endl;

    do {
        cout << "\n1. Register Customer\n2. Create Account\n3. Deposit\n4. Withdraw\n5. Transfer\n6. Show Customer Info\n7. Show Transactions\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int id;
            cout << "Enter customer name: ";
            cin >> name;
            cout << "Enter customer ID: ";
            cin >> id;
            customers.emplace_back(name, id);
            cout << "Customer registered successfully.\n";
        }
        else if (choice == 2) {
            int id, accNo;
            double balance;
            cout << "Enter customer ID: ";
            cin >> id;
            cout << "Enter new account number: ";
            cin >> accNo;
            cout << "Enter initial balance: ";
            cin >> balance;

            for (auto &cust : customers) {
                if (cust.getCustomerID() == id) {
                    cust.createAccount(accNo, balance);
                }
            }
        }
        else if (choice == 3) {
            int accNo;
            double amount;
            cout << "Enter account number: ";
            cin >> accNo;
            cout << "Enter deposit amount: ";
            cin >> amount;

            for (auto &cust : customers) {
                Account* acc = cust.getAccount(accNo);
                if (acc) acc->deposit(amount);
            }
        }
        else if (choice == 4) {
            int accNo;
            double amount;
            cout << "Enter account number: ";
            cin >> accNo;
            cout << "Enter withdrawal amount: ";
            cin >> amount;

            for (auto &cust : customers) {
                Account* acc = cust.getAccount(accNo);
                if (acc) acc->withdraw(amount);
            }
        }
        else if (choice == 5) {
            int fromAcc, toAcc;
            double amount;
            cout << "Enter source account number: ";
            cin >> fromAcc;
            cout << "Enter destination account number: ";
            cin >> toAcc;
            cout << "Enter transfer amount: ";
            cin >> amount;

            Account* src = nullptr;
            Account* dest = nullptr;

            for (auto &cust : customers) {
                if (!src) src = cust.getAccount(fromAcc);
                if (!dest) dest = cust.getAccount(toAcc);
            }

            if (src && dest) {
                src->transfer(*dest, amount);
            } else {
                cout << "Error: One or both accounts not found.\n";
            }
        }
        else if (choice == 6) {
            int id;
            cout << "Enter customer ID: ";
            cin >> id;
            for (auto &cust : customers) {
                if (cust.getCustomerID() == id) {
                    cust.showCustomerInfo();
                }
            }
        }
        else if (choice == 7) {
            int accNo;
            cout << "Enter account number: ";
            cin >> accNo;
            for (auto &cust : customers) {
                Account* acc = cust.getAccount(accNo);
                if (acc) acc->showTransactions();
            }
        }
        else if (choice == 8) {
            cout << "Exiting system. Goodbye!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 8);

    return 0;
}