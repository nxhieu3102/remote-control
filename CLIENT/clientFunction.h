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
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <chrono>
#include <linux/input.h>
#include <thread>
#include <ncurses.h>

using namespace std;

class clientFunction
{
public:
	void main_menu(int argc, char *argv[]);
	void chat(int argc, char *argv[]);
	bool receiveMessage(int &clientSd , int &bytesRead , int &bytesWritten);
	bool receiveKeyPress(int &clientSd);
};