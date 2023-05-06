#include "./clientFunction.h"

using namespace std;

clientFunction ::clientFunction(char *ip, char *_port, bool &flag)
{	
	cout << "ip: " << ip << endl;
	cout << "port: " << _port << endl;
	// grab the IP address and port number
	char *serverIp = ip;
	int port = atoi(_port);
	flag = true;
	// setup a socket and connection tools
	struct hostent *host = gethostbyname(serverIp);
	sockaddr_in sendSockAddr;
	bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
	sendSockAddr.sin_family = AF_INET;
	sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
	sendSockAddr.sin_port = htons(port);
	clientSd = socket(AF_INET, SOCK_STREAM, 0);

	// try to connect...
	int status = connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr));
	if (status < 0)
	{	
		flag = false;
		cout << " ##### Error connecting to socket." << endl;
	}
	else cout << " ##### Connected to the server." << endl;
}

void clientFunction::main_menu()
{
	system("clear");
	cout << "\n\t\t\t\t\t *WELCOME TO THE CHATROOM*";
	cout << "\n\t\t\t\t\t *************************";
	cout << "\n\t\t\t\t\t ******* MAIN MENU *******";
	cout << "\n\t\t\t\t\t *************************\n";
	chat();
}

bool clientFunction::receiveMessage(string fileName)
{
	char temp[20];
	memset(&temp, 0, sizeof(temp));
	// this->receive(sockfd, (char)&temp, sizeof(temp), 0);
	recv(clientSd, temp, sizeof(temp), 0);
	int totalDataSize = atoi(temp);
	fflush(stdin);
	std::cout << "totalDataSize: " << totalDataSize << std::endl;
	fflush(stdin);

	int bytes_received = 0;
	int bytes_to_receive = totalDataSize;

	while (bytes_received < totalDataSize)
	{
		// char temp = (char*)malloc(1024);
		char temp[1025] = {0};
		int bytes_received_now = recv(clientSd, temp, 1024, 0);
		if (bytes_received_now == -1)
		{
			std::cout << "error!\n";
			exit(1);
		}
		temp[1024] = '\0';
		// fwrite(temp,sizeof(unsigned char),bytes_received_now,fd);

		if (fileName != "")
		{
			// cout << "oke";
			FILE *fo = fopen(fileName.c_str(), "ab");
			if (!fo)
			{
				cout << "Can't open file " << fileName << "\n";
				return 0;
			}
			fwrite(temp, sizeof(char), bytes_received_now, fo);
			fclose(fo);
		}
		else
			cout << temp;

		bytes_received += bytes_received_now;
		// cout << "\n";
		// cout << bytes_received_now << " meomeo\n" ;
		// free(temp);
	}
	return bytes_received == totalDataSize;
}

bool clientFunction::receiveKeyPress(int client_Sd)
{
	cout << "Catching key pressed until you press `ESC`\n";
	const char *dev_path = "/dev/input/event1";
	int fd = open(dev_path, O_RDONLY);
	if (fd < 0)
	{
		std::cerr << "Could not open device file." << std::endl;
		return 0;
	}
	bool kt = 1, stopListening = 0;
	auto listenFromServer = [&kt, &client_Sd, &stopListening]()
	{
		char msg[50];
		while (1)
		{
			memset(&msg, 0, sizeof(msg));

			int byteRecv = recv(client_Sd, (char *)&msg, sizeof(msg), 0); // receive message
			if (byteRecv <= 0 || stopListening == 1)
			{
				// kt = 0;
				cout << "Stop listen from the Server\n";
				kt = 0;
				return;
			}

			fflush(stdin);
			// cout << "MEOMEO";
			cout << msg << "\n";
			fflush(stdin);
		}
		return;
	};

	auto listenFromClientKeyboard = [&client_Sd, &fd]()
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
				send(client_Sd, (char *)&msg, strlen(msg), 0);
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
	cin.getline(x, 1000);

	fflush(stdin);
	memset(x, 0, sizeof x);

	return kt;
}

void clientFunction::chat()
{
	// take the message
	int n = 0;
	struct timeval start1, end1;
	gettimeofday(&start1, NULL);
	int c = 1;
	// create a message buffer
	char msg[100];
	while (1)
	{

		memset(&msg, 0, sizeof(msg)); // clear the buffer
		c++;
		fflush(stdin);
		cout << "\n\t\t Client: ";

		n = 0;
		fflush(stdin);

		string data;
		getline(std::cin, data);
		memset(msg, 0, sizeof msg);

		strcpy(msg, data.c_str());
		msg[strlen(msg)] = '\0';

		// cout << msg << " " << strlen(msg) << "\n";

		if (strcmp(msg, "exit") == 0) // check if the message equals "exit" then exit
		{
			cout << "EXIT from Server.";
			send(clientSd, (char *)&msg, strlen(msg), 0);
			break;
		}

		send(clientSd, (char *)&msg, strlen(msg), 0);

		if (strlen(msg) == 0)
			break;

		if(!strcmp(msg, "1") || !strcmp(msg, "6"))
		{
			fflush(stdin);
			if(!strcmp(msg, "1"))
				cout << "Type the name of app that you want to start: ";
			else
				cout << "Type the name of app that you want to stop: ";
			fflush(stdin);
				
			getline(std::cin, data);
			memset(msg, 0, sizeof msg);

			strcpy(msg, data.c_str());
			msg[strlen(msg)] = '\0';

			send(clientSd, (char *)&msg, strlen(msg), 0);
			if (receiveMessage("") == 0)
				break;
		}
		else if (strcmp(msg, "4") == 0)
		{
			receiveKeyPress(clientSd);
			cout << "\n Press any key to continue.";
			getchar();
		}
		else if (strcmp(msg, "3") == 0)
		{
			time_t current_time = time(NULL);
			struct tm *local_time = localtime(&current_time);

			int year = local_time->tm_year + 1900;
			int month = local_time->tm_mon + 1;
			int day = local_time->tm_mday;
			int hour = local_time->tm_hour;
			int minute = local_time->tm_min;

			string filename = "screenshot-" + to_string(year) + "-" + to_string(month) + "-" + to_string(day) + "-" + to_string(hour) + "-" + to_string(minute) + ".bmp";
			cout << "Save to file name: " << filename << "\n";
			if (receiveMessage(filename) == 0)
				break;
		}
		else if (receiveMessage("") == 0)
			break;

		// cout << "Press any key to continue...";
		// getchar();
	}

	gettimeofday(&end1, NULL);
	cout << "********Session Ended********" << endl;
	cout << "Elapsed Time: " << (end1.tv_sec - start1.tv_sec) << " seconds" << endl;
	cout << "Connection Closed" << endl;

	cout << "\n\n Press any key to continue.";
	string temp;
	getline(cin, temp);
}

clientFunction ::~clientFunction()
{
	close(clientSd);
}
