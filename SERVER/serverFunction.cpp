#include "./serverFunction.h"

using namespace std;

void serverFunction ::start_server(int argc, char *argv[])
{
    // for the server, we only need to specify a port number
    if (argc != 2)
    {
        cerr << "\n\n Usage: port" << endl;
        return;
    }

    // grab the port number
    int port = atoi(argv[1]);
    // buffer to send and receive messages with
    char msg[100];

    // setup a socket and connection tools
    sockaddr_in servAddr;                         // initializes a struct to hold the server address information.
    bzero((char *)&servAddr, sizeof(servAddr));   // clears the memory for the struct.
    servAddr.sin_family = AF_INET;                // sets the address family as IPv4.
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // binds the server to all network interfaces, so it can listen on any available IP address.
    servAddr.sin_port = htons(port);              // sets the port number for the server to listen on, after converting it to network byte order using htons().

    // open stream oriented socket with internet address, also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0)
    {
        cerr << "\n\n ##### Error establishing the server socket." << endl;
        return;
    }

    // bind the socket to its local address
    int bindStatus = ::bind(serverSd, (struct sockaddr *)&servAddr,
                            sizeof(servAddr));
    if (bindStatus < 0)
    {
        cerr << "\n\n ##### Error binding socket to local address." << endl;
        return;
    }

    cout << "\n\n ##### Waiting for a client to connect." << endl;
    // listen for up to 5 requests at a time
    listen(serverSd, 5);
    // receive a request from client using accept
    // we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    // accept, create a new socket descriptor to handle the new connection with client
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    // cout << newSd << "\n";
    if (newSd < 0)
    {
        cerr << "\n\n ##### Error accepting request from client." << endl;
        return;
    }
    cout << " ##### Connected with client." << endl;

    // lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    // also keep track of the amount of data sent as well
    // cout << "S";
    while (1)
    {
        // cout << "SS\n";
        if (receiveMessage(newSd) == 0)
            break;
    }

    // we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(newSd);
    close(serverSd);
    cout << "********Session Ended********" << endl;
    // cout << "Bytes Written: " << bytesWritten << " Bytes Read: " << bytesRead << endl;
    cout << "Elapsed Time: " << (end1.tv_sec - start1.tv_sec) << " seconds" << endl;
    cout << "Connection Closed." << endl;
    return;
}

bool serverFunction ::receiveMessage(int &newSd)
{
    // receive a message from the client (listen)
    // fflush(stdin);
    cout << "\n\n Awaiting Client Response.";
    cout << "\n-----------------------------------";
    fflush(stdin);
    char msg[300];

    memset(&msg, 0, sizeof(msg)); // clear the buffer
    recv(newSd, (char *)&msg, sizeof(msg), 0);
    // msg[strlen(msg) - 1] = '\0';
    // cout << msg << " " << strlen(msg) << " " << strcmp(msg, "exit") << "\n";

    if (!strcmp(msg, "exit") || strlen(msg) <= 0)
    {
        cout << " ##### Client has quit the session." << endl;
        return 0;
    }

    if (!strcmp(msg, "1"))
    {
        cout << "\n Client: List running processes";
        vector<string> res = getRunningProcess(newSd);
        res.push_back("exit");
        for (int i = 0; i < (int)res.size(); i++)
        {
            // cout << res[i].size() << "\n";
            memset(&msg, 0, sizeof(msg));
            strcpy(msg, res[i].c_str());
            // cout << msg << "\n";
            send(newSd, (char *)&msg, strlen(msg), 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(5)); // sleep to split the message
        }
    }
    else if (!strcmp(msg, "2"))
    {
        cout << "\n Client: List installed applications";
        vector<string> res = getInstalledApp(newSd);
        res.push_back("exit");
        for (int i = 0; i < (int)res.size(); i++)
        {
            // cout << res[i].size() << "\n";
            memset(&msg, 0, sizeof(msg));
            strcpy(msg, res[i].c_str());
            // cout << msg << "\n";
            send(newSd, (char *)&msg, strlen(msg), 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    else if (!strcmp(msg, "3"))
    {
        cout << "\n Client: 3";
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, "3");
        send(newSd, (char *)&msg, strlen(msg), 0);
    }
    else if (!strcmp(msg, "4"))
    {
        cout << "\n Client: Catch key pressed until press `ESC`\n";
        catchKeyPressUntilESC(newSd);
    }
    else // if(!strcmp(msg, "2"))
    {
        cout << "\n Wrong command!!";
        memset(&msg, 0, sizeof(msg));
        strcpy(msg, "Wrong command!!");
        send(newSd, (char *)&msg, strlen(msg), 0);
    }

    return 1;
}

vector<string> serverFunction ::getInstalledApp(int &newSd)
{
    // system("apt-mark showmanual"); //list all the packages installed by users
    // system("sudo find / -type f -name \"*.sh\" -executable"); //list all file ".sh" ==> which files to install app
    // "apt-mark showmanual" //packages installed by users
    // "apt-mark showauto" //packages installed automatically

    vector<string> packages;
    FILE *pipe = popen("apt-mark showmanual", "r");

    if (!pipe)
    {
        cerr << "Failed to run command\n";
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        packages.push_back(buffer);
    }

    // for (int i = 0 ; i < (int)packages.size() ; i ++) {
    //     cout << packages[i] << "\n";
    // }
    pclose(pipe);
    return packages;
}

vector<string> serverFunction ::getRunningProcess(int &newSd)
{
    // system("ps -ef | grep -v '\\[.*\\]'"); //list all the running process

    vector<string> process;
    FILE *pipe = popen("ps -ef | grep -v '\\[.*\\]'", "r");

    if (!pipe)
    {
        cerr << "Failed to run command\n";
        exit(1);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        process.push_back(buffer);
    }

    // for (int i = 0 ; i < (int)packages.size() ; i ++) {
    //     cout << packages[i] << "\n";
    // }
    pclose(pipe);
    return process;
}

void serverFunction ::catchKeyPressUntilESC(int &newSd)
{
    const char *dev_path = "/dev/input/event1"; // Path to keyboard device file
    int fd = open(dev_path, O_RDONLY);
    if (fd < 0)
    {
        char msg[100];
        memset(&msg, 0, sizeof(msg)); // clear the buffer
        string temp = "Cannot catch keys pressed.";
        strcpy(msg , temp.c_str());
        send(newSd, (char *)&msg, strlen(msg), 0);

        std::cerr << "Could not open device file." << std::endl;
        return;
    }

    //if receive "9" from client, then stop program
    bool stop = 0;
    auto listenFromClient = [&newSd]()
    {
        char msg[30];
        while(1)
        {
            memset(&msg, 0, sizeof(msg)); // clear the buffer
            recv(newSd, (char *)&msg, sizeof(msg), 0);
            if(strlen(msg) == 0)
            	break;

            if (!strcmp(msg, "exit"))
                break;
        }
        // cout << "goy xog\n";
        return;
    };
    auto catchKey = [&newSd , &fd, &stop]()
    {
        serverFunction luu;
        char msg[100];
        string temp = "";
        while (stop == 0)
        {
            temp = "";
            struct input_event ev;
            ssize_t n = read(fd, &ev, sizeof(ev));
            if (n == sizeof(ev))
            {
                if (ev.type == EV_KEY && ev.value == 1)
                {
                    // cout << "Key " << luu.MAP[ev.code] << " was pressed." << std::endl;
                    temp += "Key " + luu.MAP[ev.code] + " was pressed.";
                    
                    memset(&msg, 0, sizeof(msg));
                    strcpy(msg, temp.c_str());
                    // cout << msg << "\n";
                    send(newSd, (char *)&msg, strlen(msg), 0);
                }
            }
        }
    };

    // serverFunction* obj = this;  // pointer to the current object
    thread func1(catchKey);
    func1.detach();

    thread func2(listenFromClient);
    // func2.detach();
    func2.join();
    
    char msg[20];
    memset(&msg, 0, sizeof(msg));
	strcpy(msg, "exit");
	send(newSd, (char *)&msg, strlen(msg), 0);
    stop = 1;

    cout << "Stop catching key pressed\n";
    close(fd);
    return;
}
