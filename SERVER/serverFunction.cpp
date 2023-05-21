#include "./serverFunction.h"

using namespace std;

serverFunction::serverFunction(char *port)
{
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    hints.ai_flags = AI_PASSIVE;     // listening for incoming connections

    strcpy(PORT, port);

    int rv = 0, yes = 1;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    //?????????

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    BACKLOG = 10;

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }
}

void *serverFunction::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

bool serverFunction::receive(int &sockfd, char *&res, int &maxLength)
{

    char temp[100];
    memset(temp, 0, sizeof(temp));

    int bytesReceived = recv(sockfd, (char *)&temp, sizeof(temp), 0);

    // cout << temp << "\n";

    if (bytesReceived >= maxLength)
    {
        cout << "\nMessage is too long!, skip...";
        return 1;
    }

    strcpy(res, temp);
    // std::cout << "total datasize to receive: " << bytesReceived << std::endl;

    return (strlen(temp)) == bytesReceived;
}

bool serverFunction::sending(int &new_fd, char *msg, int maxLength)
{
    char temp[20];
    sprintf(temp, "%d", maxLength);
    // printf("from integer to char* %s\n", temp);

    // int check = this->sending(sockfd, (char)&temp, sizeof(temp), 0);
    int check = send(new_fd, (char *)&temp, sizeof(temp), 0);
    if (check == -1)
    {
        printf("hello\n");
        exit(1);
    }

    int bytes_sent = 0;
    int bytes_to_send = maxLength;
    while (bytes_sent < maxLength)
    {
        int bytes_sent_now = send(new_fd, msg + bytes_sent, std::min(bytes_to_send, MAXBUFFERSIZE), 0);
        if (bytes_sent_now == -1)
        {
            std::cerr << "Failed to send data" << std::endl;
            exit(1);
            // return 1;
        }
        bytes_sent += bytes_sent_now;
        bytes_to_send -= bytes_sent_now;
        // cout << bytes_sent_now << " " << "meomeo" << "\n";
    }

    return bytes_to_send == 0;
}

void serverFunction::TransferData()
{
    char s[INET6_ADDRSTRLEN];

    while(1){
        printf("server: waiting for connections...\n");
        struct sockaddr_storage their_addr;
        socklen_t sin_size = sizeof their_addr;
        int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
        }

        inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s);
        printf("server: got connection from %s\n", s);

        while (1)
        {
            printf("\nClient: ");

            int length = 100;
            char *msg = (char *)malloc(length);
            memset(msg , 0 , sizeof msg);

            recv(new_fd, msg, length , 0);

            // cout << msg << " " << strlen(msg) << "\n";

            if (strcmp(msg, "exit") == 0)
            {
                printf("exit\n");
                free(msg);
                break;
            }

            int maxLength = 100;
            char *res = (char *)malloc(maxLength);
            if (strcmp(msg, "1") == 0) // Start app
            {
                memset(msg , 0 , sizeof msg);
                recv(new_fd, msg, length , 0);

                string temp(msg);

                cout << "Start app " << msg << "\n";
                if (!startApp(res , temp))
                {
                    strcpy(res, "fail to run the process\n");
                }
                maxLength = strlen(res);
            }
            else if (strcmp(msg, "6") == 0) // Stop app
            {
                memset(msg , 0 , sizeof msg);
                recv(new_fd, msg, length , 0);

                string temp(msg);

                cout << "Stop app " << msg << "\n";
                if (!stopApp(res , temp))
                {
                    strcpy(res, "fail to run the process\n");
                }
                maxLength = strlen(res);
            }
            else if (strcmp(msg, "2") == 0) // InstalledApp
            {
                cout << "Get installed apps\n";
                if (!getInstalledApp(res))
                {
                    strcpy(res, "fail to Get installed apps\n");
                }
                maxLength = strlen(res);
            }
            else if (strcmp(msg, "3") == 0) // capture screen
            {
                cout << "Screen shot\n";
                if (!ScreenShot(res , maxLength))
                {
                    strcpy(res, "fail to capture screen\n");
                }
            }
            else if (strcmp(msg, "4") == 0) // keylogger
            {
                cout << "Catching key pressed\n";
                catchKeyPressUntilESC(new_fd);
                free(msg);
                free(res);
                continue;
            }
            else if (strcmp(msg, "5") == 0) // treeCommand
            {
                cout << "Folder tree\n";
                char path[2] = ".";
                if (!TreeCommand(path, res, maxLength))
                {
                    strcpy(res, "fail to browse the directory");
                }
                maxLength = strlen(res);
        
            }
            else if (strcmp(msg, "7") == 0) // list process
            {
                cout << "Running processes\n";
                if (!getRunningProcess(res))
                {
                    strcpy(res, "fail to run the process\n");
                }
                maxLength = strlen(res);
            }
            else
            {
                fflush(stdin);
                std::cout << "\n\t\t Server: Wrong command";

                memset(res, 0, sizeof res);
                strcpy(res, "Wrong command!!");
                maxLength = strlen(res);
            }

            sending(new_fd, res , maxLength);

            if (strcmp(res, "exit") == 0)
            {
                free(msg);
                free(res);
                break;
            }
            cout << "-------------------------------------------\n";

            free(msg);
            free(res);
        }
    

    if (!fork())
    {                  // this is the child process
        close(sockfd); // child doesn't need the listener
        close(new_fd);
        exit(0);
    }

    printf("\nserver: disconnected from %s\n", s);
    close(new_fd);
    }
}

serverFunction::~serverFunction()
{
    close(sockfd);
}
