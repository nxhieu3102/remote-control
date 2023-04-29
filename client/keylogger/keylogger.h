#ifndef keylogger_h
#define keylogger_h

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

bool receiveKeyPress(int &clientSd);

#endif