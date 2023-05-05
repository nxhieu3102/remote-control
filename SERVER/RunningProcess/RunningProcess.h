#pragma once
// #ifndef RunningProcess_H
// #define RunningProcess_H

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
#include <fstream>
#include <chrono>
#include <thread>
#include <map>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
using namespace std;

bool getRunningProcess(char *&buffer);

bool startApp(char *&buffer , string appName);

bool stopApp(char *&buffer , string appName);

// #endif