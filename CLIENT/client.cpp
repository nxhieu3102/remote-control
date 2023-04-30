#include "./clientFunction.h"

#define PORT 8080

using namespace std;



int main(int argc, char *argv[])
{
	if (argc != 3) {
        std::cerr<< "usage: ./client IPAddress PortAddress\n";
        exit(1);
    }
	clientFunction u_t(argv[1],argv[2]);
	u_t.main_menu();
	return 0;
}

//	g++ -pthread CLIENT/*.cpp -o client -lncurses
//  ./client <ip> <port>
//  ./client 192.168.137.1 8080