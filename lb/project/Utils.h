#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "NetIO.h"

std::string getMaskedPassword(NetIO& io);
void calculateEMI(double principal, double rate, int months, NetIO& io);

#endif
