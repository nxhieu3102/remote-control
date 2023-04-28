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

bool clientFunction::receiveMessage(int &clientSd)
{
	char msg[300];

	cout << "\nServer: \n";
	while (1)
	{
		// receive multiple messages
		//  fflush(stdin);

		memset(&msg, 0, sizeof(msg));

		int byteRecv = recv(clientSd, (char *)&msg, sizeof(msg), 0); // receive message
		if (byteRecv <= 0)
			return 0;

		if (!strcmp(msg, "exit")) // check if the message equals "exit" then exit
		{
			cout << "--------------------------------------" << endl;
			return 1;
		}

		fflush(stdin);
		//cout << strlen(msg) << "\n";
		cout << msg << "\n";
		fflush(stdin);

	}
	return 0;
}

bool clientFunction::receiveKeyPress(int &clientSd)
{
	cout << "Catching key pressed until you press `ESC`\n";
	const char *dev_path = "/dev/input/event1";
	int fd = open(dev_path, O_RDONLY);
	if (fd < 0)
	{
		std::cerr << "Could not open device file." << std::endl;
		return 0;
	}
	bool kt = 1 , stopListening = 0;
	auto listenFromServer = [&kt, &clientSd, &stopListening]()
	{
		char msg[50];
		while (1)
		{
			memset(&msg, 0, sizeof(msg));

			int byteRecv = recv(clientSd, (char *)&msg, sizeof(msg), 0); // receive message
			if (byteRecv <= 0 || stopListening == 1)
			{
				// kt = 0;
				cout << "Stop listen from the Server\n";
				kt = 0;
				return;
			}

			fflush(stdin);
			//cout << "MEOMEO";
			cout << msg << "\n";
			fflush(stdin);
		}
		return;
	};

	auto listenFromClientKeyboard = [&clientSd, &fd]()
	{
		while (1)
		{

			struct input_event ev;
			ssize_t n = read(fd, &ev, sizeof(ev));
			if (n == sizeof(ev) && ev.type == EV_KEY && ev.value == 1 && ev.code == 1)
			{
				memset(&ev, 0, sizeof(ev));
				string temp = "exit";
				char msg[10];
				memset(msg, 0, sizeof msg);
				strcpy(msg, temp.c_str());
				send(clientSd, (char *)&msg, strlen(msg), 0);
				break;
			}
		}
		refresh();
		return;
	};

	thread func1(listenFromServer);
	func1.detach();

	thread func2(listenFromClientKeyboard);

	func2.join();
	stopListening = 1;
	// std::this_thread::sleep_for(std::chrono::milliseconds(500));

	close(fd);
	cout << "Stop catching key pressed\n";
	cout << "---------------------------\n";
	
	char x[1000];
	fflush(stdin);
	cout << "Enter to continue.\n";
	cin.getline(x , 1000);
	
	fflush(stdin);
	memset(x , 0 , sizeof x);
	
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
	int n = 0;
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
		// cout << msg << " " << strlen(msg) << "\n";
		if (strcmp(buff, "exit") == 0) // check if the message equals "exit" then exit
		{
			cout << "EXIT from Server.";
			send(clientSd, (char *)&msg, strlen(msg), 0);
			break;
		}

		send(clientSd, (char *)&msg, strlen(msg), 0);

		if (strlen(msg) == 0)
			break;

		if (strcmp(buff, "4") == 0)
			receiveKeyPress(clientSd);
		else if (receiveMessage(clientSd) == 0)
			break;
		cout << "\n\n Press any key to continue.";
		getchar();
	}

	gettimeofday(&end1, NULL);
	close(clientSd);
	cout << "********Session Ended********" << endl;
	cout << "Elapsed Time: " << (end1.tv_sec - start1.tv_sec) << " seconds" << endl;
	cout << "Connection Closed" << endl;

	cout << "\n\n Press any key to continue.";
	getchar();
}