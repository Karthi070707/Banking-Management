#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include <vector>

class Admin {
private:
    std::vector<Account> accounts;

public:
    void createAccount();
    void deleteAccount(int accNo);
    void modifyAccount(int accNo);
    void showAllAccounts() const;
    Account* getAccount(int accNo);
};

#endif
