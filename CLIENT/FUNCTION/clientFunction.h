#pragma once
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
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <chrono>
#include <linux/input.h>
#include <thread>
#include <ncurses.h>
#include <stdlib.h>

using namespace std;

class clientFunction
{
private:
	int clientSd;
	// char* ip;
	// char* _port;
public:
	clientFunction(char* ip, char* _port, bool &flag);
	void main_menu();
	void chat();
	bool receiveMessage(string fileName);
	bool receiveKeyPress(int client_Sd);
	~clientFunction();
};