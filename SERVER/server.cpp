#include "./serverFunction.h"

using namespace std;
// Server side


int main(int argc, char *argv[])
{
    serverFunction SERVER;
    SERVER.start_server(argc , argv);
    return 0;
}
//  g++ -pthread SERVER/*.cpp -o server
// ./server 8080