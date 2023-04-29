#include "server.h"

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

Server::Server(char* port) {
    memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

    strcpy(PORT,port);

    int rv = 0, yes = 1;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

    for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
				sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (p == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

    if (p == NULL)  {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}

    BACKLOG = 10;

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}


    // sa.sa_handler = *this->sigchld_handler(rv); // reap all dead processes
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = SA_RESTART;
	// if (sigaction(SIGCHLD, &sa, NULL) == -1) {
	// 	perror("sigaction");
	// 	exit(1);
	// }
}

void* Server::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// void Server::sigchld_handler(int s) {
//     (void)s; // quiet unused variable warning

// 	// waitpid() might overwrite errno, so we save and restore it:
// 	int saved_errno = errno;

// 	while(waitpid(-1, NULL, WNOHANG) > 0);

// 	errno = saved_errno;
// }

int Server::sending(int sockfd, const void* buf, size_t len, int flags) {
    int bytesSent = send(sockfd, buf, len, flags);
    return bytesSent;
}

bool Server::sending(int sockfd, char* msg) {
    int length = strlen(msg);
    char temp[20];
    sprintf(temp,"%d",length);
    printf("from integer to char* %s\n", temp);

    this->sending(sockfd, (char*)&temp, sizeof(temp), 0);

    int bytesSent = this->sending(sockfd, msg, strlen(msg), 0);
    std::cout << "bytes sent: " << bytesSent << std::endl;
    return bytesSent == length;
}

int Server::receive(int sockfd, void* buf, size_t len, int flags) {
    int bytesReceived = recv(sockfd, buf, len, flags);
    return bytesReceived;
}

bool Server::receive(int sockfd, char*& res, int& maxLength) {
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

void Server::TransferData() {
    char s[INET6_ADDRSTRLEN];

    printf("server: waiting for connections...\n");
    struct sockaddr_storage their_addr;
    socklen_t sin_size = sizeof their_addr;
    int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
        perror("accept");
    }

    inet_ntop(their_addr.ss_family,
        get_in_addr((struct sockaddr *)&their_addr),
        s, sizeof s);
    printf("server: got connection from %s\n", s);

    while (1) {
        int length = 20;
        char* msg = (char*)malloc(length);

        //memset(msg, 0, length);
        //recv(new_fd, msg, length, 0);

        this->receive(new_fd, msg, length);
        //std::cout << byteRead << std::endl;
        // int temp = htonl(byteRead);
        // send(new_fd, &temp, sizeof temp, 0);

        // char* backup = (char*)
        // if (recv(new_fd, (char*))

        printf("client: %s\n", msg);

        if (strcmp(msg, "exit") == 0) {
            printf("client exit\n");
            free(msg);
            break;
        }

        int maxLength = 20;
        char* res = (char*)malloc(maxLength);

        if (strcmp(msg, "treecommand") == 0) {
            char path[2] = ".";
            if (!TreeCommand(path, res, maxLength)) {
                strcpy(res,"fail to browse the directory\n");
            }
        // } else if (strcmp(msg, "runningprocess") == 0) {
        //     if (!RunningProcess(res,maxLength)) {
        //         strcpy(res,"fail to show the running process\n");
        //     }
        } 
        else {
            fflush(stdin); 
            std::cout <<"\n\t\t Server: ";
            std::string data;
            std::getline(std::cin, data);
            memset(res, 0, maxLength);
            concatenate(res, data.c_str(), maxLength);
        }

        if(strcmp(res,"exit") == 0)
        {
            this->sending(new_fd, res);
            free(msg);
            free(res);
            break;
        }
        
        this->sending(new_fd, res);

        free(msg);
        free(res);
    }

    if (!fork()) { // this is the child process
        close(sockfd); // child doesn't need the listener
        close(new_fd);
        exit(0);
    }

    printf("\nserver: disconnected from %s\n", s);
    close(new_fd);
}

Server::~Server() {
    close(sockfd);
}


