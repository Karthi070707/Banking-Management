#ifndef NETIO_H
#define NETIO_H

#include "../Load-Balancer-Simulator/common.h"
#include <string>

class NetIO {
private:
    sock_t fd;
public:
    NetIO(sock_t fd);
    void print(const std::string& msg);
    std::string readLine();
    int readInt();
    double readDouble();
};
#endif
