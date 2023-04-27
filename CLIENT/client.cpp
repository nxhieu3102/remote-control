#include "./clientFunction.h"

#define PORT 8080

using namespace std;



int main(int argc, char *argv[])
{
	clientFunction u_t;
	u_t.main_menu(argc, argv);
	return 0;
}

//	g++ -pthread CLIENT/*.cpp -o client -lncurses
//  ./client <ip> <port>
//  ./client 192.168.137.1 8080