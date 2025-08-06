#include "Utils.h"
#include <iostream>
#include <cmath>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
char getch() {
    char buf = 0;
    termios old = {0};
    tcgetattr(0, &old);
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &old);
    read(0, &buf, 1);
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(0, TCSADRAIN, &old);
    return buf;
}
#endif

using namespace std;

string getMaskedPassword() {
    string pass;
    char ch;
    cout << "Enter Admin Password: ";
    while ((ch = getch()) != '\n' && ch != 13) {
        if (ch == 8 && !pass.empty()) {
            cout << "\b \b";
            pass.pop_back();
        } else {
            pass += ch;
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}

void calculateEMI(double p, double r, int n) {
    r = r / 1200;
    double emi = (p * r * pow(1 + r, n)) / (pow(1 + r, n) - 1);
    cout << "Monthly EMI: " << emi << endl;
    cout << "Total Repayment: " << emi * n << endl;
}


