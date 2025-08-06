#include "Admin.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Admin::createAccount() {
    Account acc;
    acc.input();
    accounts.push_back(acc);
}

void Admin::deleteAccount(int accNo) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccNumber() == accNo) {
            accounts.erase(it);
            break;
        }
    }
}


void Admin::modifyAccount(int accNo) {
    for (auto& acc : accounts) {
        if (acc.getAccNumber() == accNo) {
            acc.modify();
            return;
        }
    }
    cout << "Account not found.\n";
}

void Admin::showAllAccounts() const {
    for (const auto& acc : accounts)
        acc.display();
}

Account* Admin::getAccount(int accNo) {
    for (auto& acc : accounts) {
        if (acc.getAccNumber() == accNo)
            return &acc;
    }
    return nullptr;
}
