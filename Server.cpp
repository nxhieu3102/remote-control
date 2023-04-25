#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;
// Server side

vector<string> getInstalledApp(int &newSd)
{
    system("apt-mark showmanual"); //list all the packages installed by users
    // "apt-mark showmanual" //packages installed by users
    // "apt-mark showauto" //packages installed automatically

    vector<string> packages;
    FILE* pipe = popen("apt-mark showmanual", "r");

    if (!pipe) {
        cerr << "Failed to run command\n";
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        packages.push_back(buffer);
    }

    // for (int i = 0 ; i < (int)packages.size() ; i ++) {
    //     cout << packages[i] << "\n";
    // }
    pclose(pipe);
    return packages;
}
vector<string> getRunningProcess(int &newSd)
{
    system("ps -ef | grep -v '\\[.*\\]'"); //list all the running process 

    vector<string> process;
    FILE* pipe = popen("ps -ef | grep -v '\\[.*\\]'", "r");

    if (!pipe) {
        cerr << "Failed to run command\n";
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        process.push_back(buffer);
    }

    // for (int i = 0 ; i < (int)packages.size() ; i ++) {
    //     cout << packages[i] << "\n";
    // }
    pclose(pipe);
    return process;
}

bool receiveMessage(int &newSd , int &bytesRead , int &bytesWritten , char *msg)
{
    // receive a message from the client (listen)
    fflush(stdin);
    cout << "\n\n Awaiting Client Response.";
    fflush(stdin);

    memset(&msg, 0, sizeof(msg)); // clear the buffer
    bytesRead += recv(newSd, (char *)&msg, sizeof(msg), 0);
    msg[strlen(msg)-1] = '\0';
    // cout << msg << " " << strlen(msg) << " " << strcmp(msg, "exit") << "\n";
    if (!strcmp(msg, "exit"))
    {
        cout << " ##### Client has quit the session." << endl;
        return 0;
    }

    cout << "-----------------------------------";
    if(!strcmp(msg, "1"))
    {
        vector<string> res = getRunningProcess(newSd);
        for (int i = 0 ; i < (int)res.size() ; i ++) {
            cout << res[i] << "\n";
        }
    }
    else if(!strcmp(msg, "2"))
    {
        vector<string> res = getInstalledApp(newSd);
        for (int i = 0 ; i < (int)res.size() ; i ++) {
            cout << res[i] << "\n";
        }
    }
    else if(!strcmp(msg, "3"))
    {

    }
    else if(!strcmp(msg, "4"))
    {

    }
    else //if(!strcmp(msg, "2"))
    {

    }
    
    
    return 1;
}

int main(int argc, char *argv[])
{
    // for the server, we only need to specify a port number
    if (argc != 2)
    {
        cerr << "\n\n Usage: port" << endl;
        exit(0);
    }

    // grab the port number
    int port = atoi(argv[1]);
    // buffer to send and receive messages with
    char msg[100];

    // setup a socket and connection tools
    sockaddr_in servAddr;                         // initializes a struct to hold the server address information.
    bzero((char *)&servAddr, sizeof(servAddr));   // clears the memory for the struct.
    servAddr.sin_family = AF_INET;                // sets the address family as IPv4.
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // binds the server to all network interfaces, so it can listen on any available IP address.
    servAddr.sin_port = htons(port);              // sets the port number for the server to listen on, after converting it to network byte order using htons().

    // open stream oriented socket with internet address, also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0)
    {
        cerr << "\n\n ##### Error establishing the server socket." << endl;
        exit(0);
    }

    // bind the socket to its local address
    int bindStatus = ::bind(serverSd, (struct sockaddr *)&servAddr,
                            sizeof(servAddr));
    if (bindStatus < 0)
    {
        cerr << "\n\n ##### Error binding socket to local address." << endl;
        exit(0);
    }

    cout << "\n\n ##### Waiting for a client to connect." << endl;
    // listen for up to 5 requests at a time
    listen(serverSd, 5);
    // receive a request from client using accept
    // we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // accept, create a new socket descriptor to handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    cout << newSd << "\n";
    if (newSd < 0)
    {
        cerr << "\n\n ##### Error accepting request from client." << endl;
        exit(1);
    }
    cout << " ##### Connected with client." << endl;

    // lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    // also keep track of the amount of data sent as well
    int bytesRead = 0, bytesWritten = 0;
    while (1)
    {
        if(receiveMessage(newSd , bytesRead , bytesWritten , msg) == 0)
            break;
            
        cout << "\n Client: " << msg;
        cout << "\n\t\t Server: ";
        string data;
        getline(cin, data);
        memset(&msg, 0, sizeof(msg)); // clear the buffer
        strcpy(msg, data.c_str());

        if (data == "exit")
        {
            // send to the client that server has closed the connection
            send(newSd, (char *)&msg, strlen(msg), 0);
            break;
        }
        // send the message to client
        bytesWritten += send(newSd, (char *)&msg, strlen(msg), 0);
    }

    // we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "********Session Ended********" << endl;
    cout << "Bytes Written: " << bytesWritten << " Bytes Read: " << bytesRead << endl;
    cout << "Elapsed Time: " << (end1.tv_sec - start1.tv_sec) << " seconds" << endl;
    cout << "Connection Closed." << endl;
    return 0;
}
// ./server 8080