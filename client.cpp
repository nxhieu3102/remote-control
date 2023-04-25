#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <iomanip>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#define PORT 8080

using namespace std;

class USER
{
public:
	friend class USER_TAG;
};

class USER_TAG : protected USER
{
public:
	void main_menu(int argc, char *argv[]);
	void chat(int argc, char *argv[]);
	bool receiveMessage(int &clientSd , int &bytesRead , int &bytesWritten);
} u_t;

void USER_TAG::main_menu(int argc, char *argv[])
{
	system("clear");
	cout << "\n\t\t\t\t\t *WELCOME TO THE CHATROOM*";
	cout << "\n\t\t\t\t\t *************************";
	cout << "\n\t\t\t\t\t ******* MAIN MENU *******";
	cout << "\n\t\t\t\t\t *************************\n";
	chat(argc, argv);
}

bool USER_TAG::receiveMessage(int &clientSd , int &bytesRead , int &bytesWritten)
{
	char msg[300];
	
	cout << "\nServer: \n";
	while (1)
	{
		//receive multiple messages
		// fflush(stdin);

		
		memset(&msg, 0, sizeof(msg));
		
		int byteRecv = recv(clientSd, (char *)&msg, sizeof(msg), 0); // receive message
		if(byteRecv == 0)
			return 0;

		bytesRead += byteRecv;
		fflush(stdin);
		cout << strlen(msg) << "\n";
		cout << msg << "\n";
		fflush(stdin);

		if (!strcmp(msg, "exit"))								   // check if the message equals "exit" then exit
		{
			cout << "--------------------------------------" << endl;
			return 1;
		}
	}
	return 0;
}

void USER_TAG::chat(int argc, char *argv[])
{
	// system("clear");

	// grab the IP address and port number
	char *serverIp = argv[1];
	int port = atoi(argv[2]);

	// setup a socket and connection tools
	struct hostent *host = gethostbyname(serverIp);
	sockaddr_in sendSockAddr;
	bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
	sendSockAddr.sin_family = AF_INET;
	sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
	sendSockAddr.sin_port = htons(port);
	int clientSd = socket(AF_INET, SOCK_STREAM, 0);

	// try to connect...
	int status = connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
	if (status < 0)
	{
		cout << " ##### Error connecting to socket." << endl;
		exit(0);
	}
	cout << " ##### Connected to the server." << endl;

	// take the message
	int bytesRead, bytesWritten = 0, n = 0;
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);
	int c = 1;
	// create a message buffer
	char msg[100] , buff[100];
	while (1)
	{
		// get the message from keyboard
		// fflush(stdin);
		c++;
		cout << "\n\t\t Client: ";
		// string data;
		// getline(cin, data);
		n = 0;
		fflush(stdin);
		while ((buff[n++] = getchar()) != '\n');
		buff[n] = '\0';

		memset(&msg, 0, sizeof(msg)); // clear the buffer
		strcpy(msg, buff);
		if (strcmp(buff, "exit") == 0) // check if the message equals "exit" then exit
		{
			send(clientSd, (char *)&msg, strlen(msg), 0);
			break;
		}

		bytesWritten += send(clientSd, (char *)&msg, strlen(msg), 0);

		if(strlen(msg) == 0 || receiveMessage(clientSd , bytesRead , bytesWritten) == 0)
			break;

		
	}

	gettimeofday(&end1, NULL);
	close(clientSd);
	cout << "********Session Ended********" << endl;
	// cout << "Bytes Written: " << bytesWritten <<" Bytes Read: " << bytesRead-c << endl;
	cout << "Elapsed Time: " << (end1.tv_sec - start1.tv_sec) << " seconds" << endl;
	cout << "Connection Closed" << endl;

	cout << "\n\n Press any key to continue.";
	getchar();
	getchar();
}

int main(int argc, char *argv[])
{
	system("clear");
	u_t.main_menu(argc, argv);
	return 0;
}

// cd code/programminglanguage/c++/sockets/Simple-Server-and-Chat-Program/UserManagement
//  ./client <ip> <port>
//  ./client 192.168.137.1 8080