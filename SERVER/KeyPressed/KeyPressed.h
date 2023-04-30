#pragma once
// #ifndef KeyPressed_H
// #define KeyPressed_H

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


void catchKeyPressUntilESC(int &newSd);

// #endif