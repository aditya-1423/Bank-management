#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;



const int  MAX_ACCOUNTS = 100;

class Account
{
private:
    int accountNumber;
    char accountHolderName[100];
    double balance;

public:
    Account()
    {
	accountNumber = 0;

	balance = 0.0;
    }
    Account(int number, char holderName[], double initialBalance)
    {
	accountNumber = number;
	strcpy(accountHolderName,holderName);
	balance = initialBalance;
    }

    int getAccountNumber() const
    {
	return accountNumber;
    }

    const char* getAccountHolderName() const
    {
	return accountHolderName;
    }

    double getBalance() const
    {
	return balance;
    }

    void deposit(double amount)
    {
	balance += amount;
    }

    int withdraw(double amount)
    {
	if (balance >= amount)
	{
	    balance -= amount;
	    return 1;
	}
	return 0;
    }
};

class Bank
{
private:
    Account accounts[MAX_ACCOUNTS];
    int numAccounts;

    

public:
    Bank() { numAccounts=0; }
void viewAllAccounts();
void viewAccountInfo();
void  withdrawFunds();
void depositFunds();
void saveAccountsToFile();
void run();
    void createAccount()
    {
        if (numAccounts >= MAX_ACCOUNTS)
        {
            cout << "Maximum number of accounts reached." << endl;
            return;
        }

        int accountNumber;
        char accountHolderName[100];
        double initialBalance;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore();

        cout << "Enter account holder name: ";
	cin>>accountHolderName;

                cout
            << "Enter initial balance: ";
        cin >> initialBalance;

        Account newAccount(accountNumber, accountHolderName, initialBalance);
        accounts[numAccounts++] = newAccount;
        saveAccountsToFile();

        cout << "Account created successfully!" << endl;
    }

    

};
void Bank :: run()
    {
        int choice;

        do
        {
            cout << "Bank Management System" << endl;
            cout << "1. Create Account" << endl;
            cout << "2. Deposit Funds" << endl;
            cout << "3. Withdraw Funds" << endl;
            cout << "4. View Account Information" << endl;
            cout << "5. View All Accounts" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                createAccount();
                break;
            case 2:
                depositFunds();
                break;
            case 3:
                withdrawFunds();
                break;
            case 4:
                viewAccountInfo();
                break;
            case 5:
                viewAllAccounts();
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    }

void Bank :: saveAccountsToFile()
    {
	ofstream outFile("bank_data.txt");

	if (!outFile)
	{
	    cerr << "Error opening file for writing!" << endl;
	    return;
	}
	     int i;
	for (i = 0; i < numAccounts; ++i)
	{
	    outFile << accounts[i].getAccountNumber() << " "
		    << accounts[i].getAccountHolderName() << " "
		    << accounts[i].getBalance() << endl;
	}

        outFile.close();
    }
void Bank:: depositFunds()
    {
        int accountNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accountNumber;

        cout << "Enter deposit amount: ";
        cin >> amount;

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                accounts[i].deposit(amount);
                saveAccountsToFile();
                cout << "Funds deposited successfully!" << endl;
                return;
            }
        }

        cout << "Account not found!" << endl;
    }

void Bank:: withdrawFunds()
    {
        int accountNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accountNumber;

        cout << "Enter withdrawal amount: ";
        cin >> amount;

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                if (accounts[i].withdraw(amount))
                {
                    saveAccountsToFile();
                    cout << "Funds withdrawn successfully!" << endl;
                }
                else
                {
                    cout << "Insufficient balance for withdrawal!" << endl;
                }
                return;
            }
        }

        cout << "Account not found!" << endl;
    }

void Bank :: viewAccountInfo()
    {
        int accountNumber;

        cout << "Enter account number: ";
        cin >> accountNumber;

        for (int i = 0; i < numAccounts; ++i)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                cout << "Account Number: " << accounts[i].getAccountNumber() << endl;
                cout << "Account Holder: " << accounts[i].getAccountHolderName() << endl;
                cout << "Balance: " << accounts[i].getBalance() << " RS" << endl;
                cout << "----------------" << endl;
                return;
            }
        }

        cout << "Account not found!" << endl;
    }
 void Bank :: viewAllAccounts()
    {
        cout << "Account Details" << endl;
        cout << "----------------" << endl;

        for (int i = 0; i < numAccounts; ++i)
        {
            cout << "Account Number: " << accounts[i].getAccountNumber() << endl;
            cout << "Account Holder: " << accounts[i].getAccountHolderName() << endl;
            cout << "Balance: " << accounts[i].getBalance() << " RS" << endl;
            cout << "----------------" << endl;
        }
    }
int main()
{
    Bank bank;
    bank.run();

    return 0;
}
