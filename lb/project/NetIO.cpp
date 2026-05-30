#include "NetIO.h"
#include <stdexcept>

NetIO::NetIO(sock_t fd) : fd(fd) {}

void NetIO::print(const std::string& msg) {
    send(fd, msg.c_str(), msg.length(), 0);
}

std::string NetIO::readLine() {
    std::string res;
    char c;
    while (recv(fd, &c, 1, 0) > 0) {
        if (c == '\r') continue;
        if (c == '\n') break;
        res += c;
    }
    return res;
}

int NetIO::readInt() {
    std::string line = readLine();
    try {
        return std::stoi(line);
    } catch(...) {
        return 0; // fallback if empty/invalid
    }
}

double NetIO::readDouble() {
    std::string line = readLine();
    try {
        return std::stod(line);
    } catch(...) {
        return 0.0;
    }
}
