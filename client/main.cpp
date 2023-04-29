#include "client.h"
//#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr<< "usage: ./client IPAddress PortAddress\n";
        exit(1);
    }
    Client cl(argv[1],argv[2]);
    cl.TransferData();
    return 0;
}