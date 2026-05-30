#include "Utils.h"
#include <iostream>
#include <cmath>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>

#endif

using namespace std;

std::string getMaskedPassword(NetIO& io) {
    // Over TCP, we can't easily mask interactively without telnet protocol negotiation.
    // So we just read a line.
    return io.readLine();
}

void calculateEMI(double p, double r, int n, NetIO& io) {
    r = r / 1200;
    double emi = (p * r * std::pow(1 + r, n)) / (std::pow(1 + r, n) - 1);
    io.print("Monthly EMI: " + std::to_string(emi) + "\n");
    io.print("Total Repayment: " + std::to_string(emi * n) + "\n");
}


