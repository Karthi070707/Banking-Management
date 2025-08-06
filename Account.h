#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>

class Account {
private:
    int accNumber;
    std::string name;
    double balance;
    std::vector<std::string> history;

public:
    void input();
    void display() const;
    void modify();
    void deposit(double amt);
    bool withdraw(double amt);
    void addHistory(const std::string& entry);
    void exportStatement() const;

    int getAccNumber() const;
};

#endif
