#include "./serverFunction.h"

using namespace std;
// Server side


int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "usage: ./server PortAddress\n";
        exit(1);
    }

    serverFunction SERVER(argv[1]);
    SERVER.TransferData();
    return 0;
}
//  g++ -pthread SERVER/*.cpp -o server
// ./server 8080