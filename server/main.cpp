#include "server.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: ./server PortAddress\n";
        exit(1);
    }
    Server sv(argv[1]);
    sv.TransferData();
    return 0;
}