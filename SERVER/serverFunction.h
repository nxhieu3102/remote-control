#pragma once
// #ifndef serverFunction_H
// #define serverFunction_H

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

#include "./InstalledApp/InstalledApp.h"
#include "./RunningProcess/RunningProcess.h"
#include "./KeyPressed/KeyPressed.h"
#include "./TreeCommand/TreeCommand.h"
#include "./ScreenShotter/ScreenShotter.h"

using namespace std;

class serverFunction
{
    private:
        const int MAXBUFFERSIZE = 1024;
        int sockfd;
        struct addrinfo hints, *servinfo, *p;
        struct sigaction sa;
        char PORT[5];
        int BACKLOG;

    public:
        serverFunction(char* port);
        void* get_in_addr(struct sockaddr *sa);
        bool receive(int &sockfd, char*& res, int& maxLength);
        bool sending(int &new_fd, char *msg, int maxLength);
        void TransferData();
        ~serverFunction();
};

// #endif