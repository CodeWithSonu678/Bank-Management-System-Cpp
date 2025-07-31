#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// 🔧 Helper trim function to remove extra spaces
string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}
class Bank
{
private:
    string accountNumber;
    string accountHolder;
    double accountBalance;

public:
    Bank()
    {
    }

    Bank(string accountHolder, string accountNumber, double accountBalance)
    {
        this->accountHolder = accountHolder;
        this->accountNumber = accountNumber;
        this->accountBalance = accountBalance;
    }

    void display() const
    {
        cout << "👤 Account Holder : " << accountHolder
             << " | 🆔 Account Number : " << accountNumber
             << " | 💰 Balance : " << accountBalance << " |" << endl;
    }
    string tofileformate() const
    {
        return accountHolder + "|" + accountNumber + "|" + to_string(accountBalance) + "|";
    }

    // ✅ Safe string parsing using stringstream
    static Bank fromfile(const string &line)
    {

        Bank b;
        stringstream ss(line);
        string balanceStr;

        if (getline(ss, b.accountHolder, '|') &&
            getline(ss, b.accountNumber, '|') &&
            getline(ss, balanceStr, '|'))
        {
            b.accountHolder = trim(b.accountHolder);
            b.accountNumber = trim(b.accountNumber);
            b.accountBalance = stod(trim(balanceStr));
        }
        else
        {
            throw runtime_error("File line format incorrect: " + line);
        }

        return b;
    }

    // Balance View
    double getbalance() const
    {
        cout << "💳 Total Balance : " << accountBalance << endl;
        return accountBalance;
    }

    // Create Account
    void CreateAccount(vector<Bank> &accounts)
    {
        cout << "\n📝 --- Create New Account ---\n";

        cout << "Enter Your Name : ";
        getline(cin, accountHolder);
        cout << "Enter Your Account Number : ";
        getline(cin, accountNumber);
        cout << "Enter your intial amount to deposit : ";
        cin >> accountBalance;
        cin.ignore();

        accounts.push_back(Bank(accountHolder, accountNumber, accountBalance));
        cout << "Account Create is successfully !\n"
             << endl;
    }

    // Deposit ke liye
    void deposit()
    {
        double amount;
        cout << "Enter your amount to deposit : ";
        cin >> amount;
        cin.ignore();

        if (amount > 0)
        {
            accountBalance += amount;
            cout << "Deposit : " << amount << " Successfull !" << endl;
        }
        else
        {
            cout << "Invalid Deposit Amount !" << endl;
        }
    }

    // Withdraul ke liye
    void withdraul()
    {
        double amount;
        cout << "Enter your amount to withdraul : ";
        cin >> amount;
        if (amount > 0 && amount <= accountBalance)
        {
            accountBalance -= amount;
            cout << "Withdraul : " << amount << " is successful !" << endl;
        }
        else
        {
            cout << "Invalid Withdraul Amount !" << endl;
        }
    }

    // display All Accounts

    static void ViewAccount(const vector<Bank> &accounts)
    {
        if (accounts.empty())
        {
            cout << "No accounts to display.\n";
        }
        else
        {
            for (auto &acc : accounts)
            {
                acc.display();
            }
        }
    }

    // Search Account

    static int SearchAccount(const vector<Bank> &accounts, const string AccNum)
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].accountNumber == AccNum)
                return i;
        }

        return -1;
    }

    // Delete Account
    static void DeleteAccount(vector<Bank> &accounts, const string AccNum)
    {
        int index = SearchAccount(accounts, AccNum);
        if (index != -1)
        {
            accounts.erase(accounts.begin() + index);
            cout << "Account 🗑️ delete is successful !" << endl;
        }
        else
        {
            cout << "Invalid Account Number !" << endl;
        }
    }

    // Update Feature
    static void UpdateAccount(vector<Bank> &accounts, const string AccNum)
    {
        int index = SearchAccount(accounts, AccNum);
        if (index != -1)
        {
            string accholder, accnum;
            cout << "--- Account Update Details ---" << endl;
            cout << "Enter your new Name : ";
            getline(cin, accholder);
            cout << "Enter your new account number : ";
            getline(cin, accnum);
            accounts[index].accountHolder = accholder;
            accounts[index].accountNumber = accnum;

            cout << "Account 🔄 Update is successful !" << endl;
        }
        else
        {
            cout << "Invalid Account Number !" << endl;
        }
    }
};

void loadfile(vector<Bank> &accounts)
{
    accounts.clear();
    ifstream out("Accounts_Records.txt");
    if (!out)
    {
        cout << "File is not open" << endl;
        return;
    }
    string line;
    while (getline(out, line))
    {
        Bank b = Bank::fromfile(line);
        accounts.push_back(b);
    }
    out.close();
}
void savefile(const vector<Bank> &accounts)
{
    ofstream out("Accounts_Records.txt");
    for (auto &acc : accounts)
    {
        out << acc.tofileformate() << endl;
    }

    out.close();
}

int main()
{
    vector<Bank> accounts;
    loadfile(accounts);
    int choice;
    Bank myaccount;
    string AccNum;
    do
    {
        cout << "-------------------------" << endl;
        cout << "🏦 BANKING SYSTEM MENU" << endl;
        cout << "-------------------------" << endl;

        cout << "1.✅ Create Account" << endl;
        cout << "2.💰 Deposit Money" << endl;
        cout << "3.💸 Withdraw Money" << endl;
        cout << "4.📄 View Balance" << endl;
        cout << "5.🗑️ Delete Account" << endl;
        cout << "6.🔄  Update Account" << endl;
        cout << "7.📋 Display All Accounts" << endl;
        cout << "8. 🔍 Search Account" << endl;
        cout << "9.🚪 Exit" << endl;

        cout << "Enter your choice : ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            myaccount.CreateAccount(accounts);
            break;
        case 2:
        {
            cout << "Enter your account number to deposit: ";
            getline(cin, AccNum);

            int i = Bank::SearchAccount(accounts, AccNum);
            if (i != -1)
            {
                accounts[i].deposit();
            }
            else
            {
                cout << "Account not found!" << endl;
            }

            break;
        }
        case 3:
        {
            cout << "Enter your account number to withdraul : ";
            getline(cin, AccNum);

            int i = Bank::SearchAccount(accounts, AccNum);
            if (i != -1)
            {
                accounts[i].withdraul();
            }
            else
            {
                cout << "Account not found!" << endl;
            }

            break;
        }
        case 4:
        {
            cout << "Enter your account number to search balacnce : ";
            getline(cin, AccNum);

            int i = Bank::SearchAccount(accounts, AccNum);
            if (i != -1)
            {
                accounts[i].getbalance();
            }
            else
            {
                cout << "Account not found!" << endl;
            }

            break;
        }
        case 5:
        {
            cout << "Enter your account number to delete : ";
            getline(cin, AccNum);
            Bank::DeleteAccount(accounts, AccNum);

            break;
        }
        case 6:
        {
            cout << "Enter your account number to update : ";
            getline(cin, AccNum);
            Bank::UpdateAccount(accounts, AccNum);
            break;
        }
        case 7:
            Bank::ViewAccount(accounts);
            break;
        case 8:
        {
            cout << "Enter your account number to serach : ";
            getline(cin, AccNum);
            int i = Bank::SearchAccount(accounts, AccNum);
            if (i != -1)
            {
                accounts[i].display();
            }
            else
            {
                cout << "Invalid Account number !" << endl;
            }

            break;
        }
        case 9:
        {
            savefile(accounts);
            cout << "All accounts saved to file successfully." << endl;
            cout << "Exit the program ....." << endl;
            break;
        }
        default:
            cout << "Enter the correct choice !" << endl;
            break;
        }

    } while (choice != 9);

    return 0;
}
