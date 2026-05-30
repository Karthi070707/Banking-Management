#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"
#include "NetIO.h"
#include <vector>

class Admin {
private:
    std::vector<Account> accounts;

public:
    void createAccount(NetIO& io);
    void deleteAccount(int accNo);
    void modifyAccount(int accNo, NetIO& io);
    void showAllAccounts(NetIO& io) const;
    Account* getAccount(int accNo);
};

#endif
