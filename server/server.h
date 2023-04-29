#ifndef server_h
#define server_h

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
//#include <sys/stat.h>
//#include <dirent.h>
//#include "stringProcess.h"
#include "./treecommand/treecommand.h"
#include "stringProcess.h"

// void concatenate(char*& res, const char* buf, int &maxLength) {
//     int length = strlen(res) + strlen(buf) + 1;
//     if (length > maxLength) {
//         maxLength = length;
//         char temp[maxLength];
//         strcpy(temp, res);
//         for (int i = 0; i < strlen(buf); i++) {
//             temp[i + strlen(res)] = buf[i];
//         }
//         temp[maxLength - 1] = '\0';
//         free(res);
//         res = (char*)malloc(maxLength * 2);
//         strcpy(res,temp);
//         maxLength += maxLength;
//     } else {
//         int idx = strlen(res);
//         for (int i = idx; i < length - 1; i++) {
//             res[i] = buf[i - idx];
//         }
//         res[length - 1] = '\0';
//     }
// }


class Server {
    private:
        int sockfd;
        struct addrinfo hints, *servinfo, *p;
        struct sigaction sa;
        char PORT[5];
        int BACKLOG;
    public:
        Server(char* port);

        void* get_in_addr(struct sockaddr *sa);
        //bool getaddrinfo();
        //void sigchld_handler(int s);
        bool sending(int sockfd, char* msg);
        int sending(int sockfd, const void* buf, size_t len, int flags);
        bool receive(int sockfd, char*& res, int& maxLength);
        int receive(int sockfd, void* buf, size_t len, int flags);

        //bool TreeCommand(char* path, char*& res, int& maxLength);
        void TransferData();

        ~Server();
};

#endif