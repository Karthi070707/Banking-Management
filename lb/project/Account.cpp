#include "Account.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void Account::input(NetIO& io) {
    io.print("Enter Account Number: ");
    accNumber = io.readInt();
    io.print("Enter Name: ");
    name = io.readLine();
    io.print("Enter Opening Balance: ");
    balance = io.readDouble();
    addHistory("Account created with balance: " + to_string(balance));
}

void Account::display(NetIO& io) const {
    io.print("Acc No: " + to_string(accNumber) + ", Name: " + name + ", Balance: " + to_string(balance) + "\n");
}

void Account::modify(NetIO& io) {
    io.print("Enter New Name: ");
    name = io.readLine();
    io.print("Enter Balance to add : ");
    int nb = io.readInt();
    balance += nb;
    addHistory("Account modified.");
}

void Account::deposit(double amt) {
    balance += amt;
    addHistory("Deposited: " + to_string(amt));
}

bool Account::withdraw(double amt) {
    if (amt > balance) return false;
    balance -= amt;
    addHistory("Withdrawn: " + to_string(amt));
    return true;
}

void Account::addHistory(const string& entry) {
    time_t now = time(0);
    history.push_back(string(ctime(&now)) + ": " + entry);
}


void Account::exportStatement() const {
    ofstream out("accounts.txt", ios::app);
    out << "Statement for Account " << accNumber << " - " << name << ":\n";
    for (const auto& h : history)
        out << h << "\n";
    out << "----------------------\n";
    out.close();
}

int Account::getAccNumber() const {
    return accNumber;
}
