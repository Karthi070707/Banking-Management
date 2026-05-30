#include "Admin.h"
#include "Utils.h"
#include "NetIO.h"
#include "../Load-Balancer-Simulator/common.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

Admin admin;
mutex_t bank_mutex;

#ifdef _WIN32
DWORD WINAPI handle_client(LPVOID arg) {
#else
void *handle_client(void *arg) {
#endif
    sock_t fd = (sock_t)(intptr_t)arg;
    NetIO io(fd);

    io.print("enter Admin password : \n");
    string password = getMaskedPassword(io);

    if (password != "admin123") {
        io.print("Access Denied.\n");
        CLOSE_SOCKET(fd);
        return 0;
    }

    int choice;
    do {
        io.print("\n1.Create\n2.Delete\n3.Modify\n4.Show\n5.Deposit\n6.Withdraw\n7.Loan EMI\n8.Export\n9.Exit\nChoice: ");
        choice = io.readInt();

        MUTEX_LOCK(bank_mutex);
        switch (choice) {
            case 1: admin.createAccount(io); break;
            case 2: {
                io.print("Acc No: ");
                int no = io.readInt();
                admin.deleteAccount(no); break;
            }
            case 3: {
                io.print("Acc No: ");
                int no = io.readInt();
                admin.modifyAccount(no, io); break;
            }
            case 4: admin.showAllAccounts(io); break;
            case 5: {
                io.print("Acc No: ");
                int no = io.readInt();
                io.print("Amount: ");
                double amt = io.readDouble();
                Account* acc = admin.getAccount(no);
                if (acc) acc->deposit(amt);
            } break;
            case 6: {
                io.print("Acc No: ");
                int no = io.readInt();
                io.print("Amount: ");
                double amt = io.readDouble();
                Account* acc = admin.getAccount(no);
                if (acc && !acc->withdraw(amt)) io.print("Insufficient funds!\n");
            } break;
            case 7: {
                io.print("Principal: "); double p = io.readDouble();
                io.print("Rate: "); double r = io.readDouble();
                io.print("Months: "); int n = io.readInt();
                calculateEMI(p, r, n, io);
            } break;
            case 8: {
                io.print("Acc No: ");
                int no = io.readInt();
                Account* acc = admin.getAccount(no);
                if (acc) acc->exportStatement();
            } break;
        }
        MUTEX_UNLOCK(bank_mutex);
    } while (choice != 9);

    io.print("Goodbye.\n");
    CLOSE_SOCKET(fd);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <port>\n";
        return 1;
    }

    int port = atoi(argv[1]);
    if (sock_init() != 0) return 1;

    MUTEX_INIT(bank_mutex);

    sock_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) == SOCK_ERR) return 1;
    if (listen(server_fd, MAX_PENDING) == SOCK_ERR) return 1;

    cout << "Bank Server running on port " << port << endl;

    for (;;) {
        struct sockaddr_in client_addr;
        int addrlen = sizeof(client_addr);
        sock_t client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
        if (client_fd == INVALID_SOCK) continue;

        thread_t t;
        if (thread_create(&t, handle_client, (void*)(intptr_t)client_fd) == 0) {
            thread_detach(t);
        } else {
            CLOSE_SOCKET(client_fd);
        }
    }

    CLOSE_SOCKET(server_fd);
    MUTEX_DESTROY(bank_mutex);
    sock_cleanup();
    return 0;
}
