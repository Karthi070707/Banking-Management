#include "Admin.h"
#include "Utils.h"
#include <iostream>
using namespace std;

int main() {
    cout<<"enter Admin password : \n";
    Admin admin;
    string password = getMaskedPassword();

    if (password != "admin123") {
        cout << "Access Denied.\n";
        return 0;
    }

    int choice;
    do {
        cout << "\n1.Create\n2.Delete\n3.Modify\n4.Show\n5.Deposit\n6.Withdraw\n7.Loan EMI\n8.Export\n9.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: admin.createAccount(); break;
            case 2: {
                int no; cout << "Acc No: "; cin >> no;
                admin.deleteAccount(no); break;
            }
            case 3: {
                int no; cout << "Acc No: "; cin >> no;
                admin.modifyAccount(no); break;
            }
            case 4: admin.showAllAccounts(); break;
            case 5: {
                int no; double amt;
                cout << "Acc No & Amount: "; cin >> no >> amt;
                Account* acc = admin.getAccount(no);
                if (acc) acc->deposit(amt);
            } break;
            case 6: {
                int no; double amt;
                cout << "Acc No & Amount: "; cin >> no >> amt;
                Account* acc = admin.getAccount(no);
                if (acc && !acc->withdraw(amt)) cout << "Insufficient funds!\n";
            } break;
            case 7: {
                double p, r; int n;
                cout << "Principal, Rate, Months: ";
                cin >> p >> r >> n;
                calculateEMI(p, r, n);
            } break;
            case 8: {
                int no;
                cout << "Acc No: "; 
                cin >> no;
                Account* acc = admin.getAccount(no);
                if (acc) acc->exportStatement();
            } break;
        }
    } while (choice != 9);

    return 0;
}

