#include "./clientFunction.h"

using namespace std;

void clientFunction::main_menu(int argc, char *argv[])
{
	system("clear");
	cout << "\n\t\t\t\t\t *WELCOME TO THE CHATROOM*";
	cout << "\n\t\t\t\t\t *************************";
	cout << "\n\t\t\t\t\t ******* MAIN MENU *******";
	cout << "\n\t\t\t\t\t *************************\n";
	chat(argc, argv);
}

bool clientFunction::receiveMessage(int &clientSd, int &bytesRead, int &bytesWritten)
{
	char msg[300];

	cout << "\nServer: \n";
	while (1)
	{
		// receive multiple messages
		//  fflush(stdin);

		memset(&msg, 0, sizeof(msg));

		int byteRecv = recv(clientSd, (char *)&msg, sizeof(msg), 0); // receive message
		if (byteRecv == 0)
			return 0;

		bytesRead += byteRecv;
		fflush(stdin);
		// cout << strlen(msg) << "\n";
		cout << msg << "\n";
		fflush(stdin);

		if (!strcmp(msg, "exit")) // check if the message equals "exit" then exit
		{
			cout << "--------------------------------------" << endl;
			return 1;
		}
	}
	return 0;
}

bool clientFunction::receiveKeyPress(int &clientSd)
{
	const char *dev_path = "/dev/input/event1";
	int fd = open(dev_path, O_RDONLY);
	if (fd < 0)
	{
		std::cerr << "Could not open device file." << std::endl;
		return 0;
	}
	bool kt = 1;
	auto listenFromServer = [&kt, &clientSd]()
	{
		char msg[50];
		while (1)
		{
			memset(&msg, 0, sizeof(msg));

			int byteRecv = recv(clientSd, (char *)&msg, sizeof(msg), 0); // receive message
			if (byteRecv == 0)
			{
				// kt = 0;
				cout << "QUICK\n";
				kt = 0;
				return;
			}

			fflush(stdin);
			cout << msg << "\n";
			fflush(stdin);
		}
		// return;
	};

	auto listenFromClientKeyboard = [&clientSd, &fd]()
	{
		// Initialize ncurses
    		
		initscr();
		cbreak();
		noecho();
		
		//int posy, posx;
    		//getyx(stdscr, posy, posx);
		
		//move(posy, posx);
		char x;
		while (x = getch()) //ESC
		{
			int temp = (int)x;
			// move(posy + 1, posx);
			cout << x << "\n" << temp << "\n";
			if(temp == 27)
			{
			string temp = "exit";
	 		char msg[10];
	 		memset(msg, 0, sizeof msg);
	 		strcpy(msg, temp.c_str());
	 		send(clientSd, (char *)&msg, strlen(msg), 0);
				cout << "BREAK";
				break;
			}
        		refresh();
		}
		// Clean up ncurses
		endwin();

		// struct input_event ev;
		// while (1)
		// {
		// 	//tcflush(fd, TCIFLUSH);
		// 	ssize_t n = read(fd, &ev, sizeof(ev));
		// 	std::string line;
		// 	std::getline(std::cin, line);
		// 	if (n == sizeof(ev) && ev.type == EV_KEY && ev.value == 1 && ev.code == 1)
		// 	{
		// 		string temp = "exit";
		// 		char msg[10];
		// 		memset(msg, 0, sizeof msg);
		// 		strcpy(msg, temp.c_str());
		// 		send(clientSd, (char *)&msg, strlen(msg), 0);
		// 		break;
		// 	}
		// 	// cin.ignore(numeric_limits<streamsize>::max(), '\n');
		// 	// fflush(stdin);
		// }
		//refresh();
		cout << "break loop\n";
		return;
	};

	thread func1(listenFromServer);
	func1.detach();

	thread func2(listenFromClientKeyboard);

	func2.join();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	cout << "Stop catching key pressed\n";
	cout << "---------------------------\n";
	close(fd);
	return kt;
}

void clientFunction::chat(int argc, char *argv[])
{
	// system("clear");

	// grab the IP address and port number
	char *serverIp = argv[1];
	int port = atoi(argv[2]);

	// setup a socket and connection tools
	struct hostent *host = gethostbyname(serverIp);
	sockaddr_in sendSockAddr;
	bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
	sendSockAddr.sin_family = AF_INET;
	sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
	sendSockAddr.sin_port = htons(port);
	int clientSd = socket(AF_INET, SOCK_STREAM, 0);

	// try to connect...
	int status = connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
	if (status < 0)
	{
		cout << " ##### Error connecting to socket." << endl;
		return;
	}
	cout << " ##### Connected to the server." << endl;

	// take the message
	int bytesRead, bytesWritten = 0, n = 0;
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);
	int c = 1;
	// create a message buffer
	char msg[100], buff[100];
	while (1)
	{
		// get the message from keyboard
		// fflush(stdin);
		memset(&msg, 0, sizeof(msg)); // clear the buffer
		memset(&buff, 0, sizeof(buff));
		c++;
		fflush(stdin);
		cout << "\n\t\t Client: ";
		// string data;
		// getline(cin, data);
		n = 0;
		fflush(stdin);
		while ((buff[n++] = getchar()) != '\n')
			; // get the endline character
		buff[n - 1] = '\0';

		strcpy(msg, buff);
		cout << msg << " " << strlen(msg) << "\n";
		if (strcmp(buff, "exit") == 0) // check if the message equals "exit" then exit
		{
			send(clientSd, (char *)&msg, strlen(msg), 0);
			break;
		}

		bytesWritten += send(clientSd, (char *)&msg, strlen(msg), 0);

		if (strlen(msg) == 0)
			break;

		if (strcmp(buff, "4") == 0)
			receiveKeyPress(clientSd);
		else if (receiveMessage(clientSd, bytesRead, bytesWritten) == 0)
			break;

		cin.clear();
		fflush(stdin);
		cout << "\n\n Press any key to continue.";
		getchar();
		fflush(stdin);
	}

	gettimeofday(&end1, NULL);
	close(clientSd);
	cout << "********Session Ended********" << endl;
	// cout << "Bytes Written: " << bytesWritten <<" Bytes Read: " << bytesRead-c << endl;
	cout << "Elapsed Time: " << (end1.tv_sec - start1.tv_sec) << " seconds" << endl;
	cout << "Connection Closed" << endl;

	cout << "\n\n Press any key to continue.";
	getchar();
	getchar();
}