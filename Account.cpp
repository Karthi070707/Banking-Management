#include "Account.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void Account::input() {
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Opening Balance: ";
    cin >> balance;
    addHistory("Account created with balance: " + to_string(balance));
}

void Account::display() const {
    cout << "Acc No: " << accNumber << ", Name: " << name << ", Balance: " << balance << endl;
}

void Account::modify() {
    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Balance to add : ";
    int nb;
    cin >> nb;
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
