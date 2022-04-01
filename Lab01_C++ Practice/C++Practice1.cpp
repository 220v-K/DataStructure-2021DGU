
#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

class bank
{
    char name[20];
    int acno;
    char actype[4];
    float balance;

public:
    void init();
    void deposit();
    void withdraw();
    void disp_det();
};
//member functions of bank class
void bank::init()
{
    cout << endl << "New Account" << endl;

    cout << "Enter the Name of the depositor : ";
    cin >> name;

    bank name;

    cout << "Enter the Account Number : ";
    cin >> acno;

    cout << "Enter the Account Type : (CURR / SAVG / FD / RD / DMAT) ";
    cin >> actype;

    cout << "Enter the Amount to Deposit : ";
    cin >> balance;
}
void bank::deposit()
{
    float balance_plus;

    cout << endl << "Depositing" << endl;

    cout << "Enter the amount to deposit : ";
    cin >> balance_plus;

    balance += balance_plus;
}
void bank::withdraw()
{
    float balance_minus;

    cout << endl << "Withdrwal" << endl;
    cout << "Enter the amount to withdraw : ";
    cin >> balance_minus;
    balance -= balance_minus;
}
void bank::disp_det()
{
    cout << endl << "Account Details";
    cout << endl << "Name of the depositor : " << name;
    cout << endl << "Acount Number : " << acno;
    cout << endl << "Account Type : " << actype;
    cout << endl << "Balance : $" << balance << endl;
}
// main function , exectution starts here
void main(void)
{
    // clrscr();
    bank obj;
    int choice = 1;
    while (choice != 0)
    {
        cout << "Enter 0 to exit\n1. Initialize a new acc.\n2. Deposit\n3. Withdraw\n4. See A / c Status\n";
        cin >> choice;
        cin.ignore(); 
        switch (choice)
        {
        case 0:
            obj.disp_det();
            cout << "EXITING PROGRAM.";
            break;
        case 1:
            obj.init();
            break;
        case 2:
            obj.deposit();
            break;
        case 3:
            obj.withdraw();
            break;
        case 4:
            obj.disp_det();
            break;
        default:
            cout << "Illegal Option" << endl;
        }
    }
    _getch();
}