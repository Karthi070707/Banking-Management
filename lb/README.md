# Bank Application with TCP Load Balancer

This project contains a simulated Banking Server (`project/`) that runs behind a custom TCP Load Balancer (`Load-Balancer-Simulator/`). The Load Balancer automatically spawns multiple instances of the banking server as worker nodes, distributing incoming traffic among them to ensure reliability and scalability.

## Architecture

- **Bank Server (`project/`)**: A C++ application handling banking operations like account creation, deposits, withdrawals, etc.
- **Load Balancer (`Load-Balancer-Simulator/`)**: A C application that routes incoming client connections on port `8080` to the bank server workers using a Least-Connections algorithm. It automatically spawns instances of `banking.exe` on startup.
- **Client**: A simple test client to interact with the Load Balancer over TCP.

## Prerequisites

- GCC / MinGW (for compiling C/C++ code)
- Make (optional, but helpful for building the load balancer)

## Compilation Instructions

### 1. Compile the Bank Server
Navigate to the `project` directory and compile the banking application:
```bash
cd project
g++ -o banking.exe Account.cpp Admin.cpp NetIO.cpp Utils.cpp main.cpp -lws2_32
cd ..
```

### 2. Compile the Load Balancer and Client
Navigate to the `Load-Balancer-Simulator` directory and build the load balancer tools:
```bash
cd Load-Balancer-Simulator
make
cd ..
```
*(If `make` is not available, you can compile them manually:)*
```bash
cd Load-Balancer-Simulator
gcc -Wall -O2 -o load_balancer.exe load_balancer.c -lws2_32
gcc -Wall -O2 -o client.exe client.c -lws2_32
cd ..
```

## How to Run

### 1. Start the Load Balancer
The Load Balancer needs to be run from its directory so it can correctly find and spawn the `banking.exe` workers.

```bash
cd Load-Balancer-Simulator
./load_balancer.exe
```

When started, it will automatically spawn 3 instances of `..\project\banking.exe` on ports `9001`, `9002`, and `9003`.

### 2. Connect a Client
In a new terminal window, connect to the Load Balancer (which listens on port `8080` by default):

```bash
cd Load-Balancer-Simulator
./client.exe
```

*Alternatively, you can use Netcat or Telnet:*
```bash
nc 127.0.0.1 8080
```

### 3. Using the Banking App
Once connected, you will be prompted for the Admin password.
- **Password:** `admin123`

You can then choose from the menu options to Create, Delete, Modify, Show accounts, and perform transactions.
