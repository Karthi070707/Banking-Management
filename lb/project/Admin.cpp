#include "Admin.h"
#include <iostream>
#include <algorithm>
using namespace std;

void Admin::createAccount(NetIO& io) {
    Account acc;
    acc.input(io);
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


void Admin::modifyAccount(int accNo, NetIO& io) {
    for (auto& acc : accounts) {
        if (acc.getAccNumber() == accNo) {
            acc.modify(io);
            return;
        }
    }
    io.print("Account not found.\n");
}

void Admin::showAllAccounts(NetIO& io) const {
    for (const auto& acc : accounts)
        acc.display(io);
}

Account* Admin::getAccount(int accNo) {
    for (auto& acc : accounts) {
        if (acc.getAccNumber() == accNo)
            return &acc;
    }
    return nullptr;
}
