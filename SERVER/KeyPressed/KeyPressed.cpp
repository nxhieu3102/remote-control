#include "./KeyPressed.h"

using namespace std;

map<int, string> MAP = {
    {0, "RESERVED"},
    {1, "ESC"},
    {2, "1"},
    {3, "2"},
    {4, "3"},
    {5, "4"},
    {6, "5"},
    {7, "6"},
    {8, "7"},
    {9, "8"},
    {10, "9"},
    {11, "0"},
    {12, "MINUS"},
    {13, "EQUAL"},
    {14, "BACKSPACE"},
    {15, "TAB"},
    {16, "Q"},
    {17, "W"},
    {18, "E"},
    {19, "R"},
    {20, "T"},
    {21, "Y"},
    {22, "U"},
    {23, "I"},
    {24, "O"},
    {25, "P"},
    {26, "LEFTBRACE"},
    {27, "RIGHTBRACE"},
    {28, "ENTER"},
    {29, "LEFTCTRL"},
    {30, "A"},
    {31, "S"},
    {32, "D"},
    {33, "F"},
    {34, "G"},
    {35, "H"},
    {36, "J"},
    {37, "K"},
    {38, "L"},
    {39, "SEMICOLON"},
    {40, "APOSTROPHE"},
    {41, "GRAVE"},
    {42, "LEFTSHIFT"},
    {43, "BACKSLASH"},
    {44, "Z"},
    {45, "X"},
    {46, "C"},
    {47, "V"},
    {48, "B"},
    {49, "N"},
    {50, "M"},
    {51, "COMMA"},
    {52, "DOT"},
    {53, "SLASH"},
    {54, "RIGHTSHIFT"},
    {55, "KPASTERISK"},
    {56, "LEFTALT"},
    {57, "SPACE"},
    {58, "CAPSLOCK"},
    {59, "F1"},
    {60, "F2"},
    {61, "F3"},
    {62, "F4"},
    {63, "F5"},
    {64, "F6"},
    {65, "F7"},
    {66, "F8"},
    {67, "F9"},
    {68, "F10"},
    {69, "NUMLOCK"},
    {70, "SCROLLLOCK"},
    {71, "KP7"},
    {72, "KP8"},
    {73, "KP9"},
    {74, "KPMINUS"},
    {75, "KP4"},
    {76, "KP5"},
    {77, "KP6"},
    {78, "KPPLUS"},
    {79, "KP1"},
    {80, "KP2"},
    {81, "KP3"},
    {82, "KP0"},
    {83, "KPDOT"},
    {85, "ZENKAKUHANKAKU"},
    {86, "102ND"},
    {87, "F11"},
    {88, "F12"},
    {89, "RO"},
    {90, "KATAKANA"},
    {91, "HIRAGANA"},
    {92, "HENKAN"},
    {93, "KATAKANAHIRAGANA"},
    {94, "MUHENKAN"},
    {95, "KPJPCOMMA"},
    {96, "KPENTER"},
    {97, "RIGHTCTRL"},
    {98, "KPSLASH"},
    {99, "SYSRQ"},
    {100, "RIGHTALT"},
    {101, "LINEFEED"},
    {102, "HOME"},
    {103, "UP"},
    {104, "PAGEUP"},
    {105, "LEFT"},
    {106, "RIGHT"},
    {107, "END"},
    {108, "DOWN"},
    {109, "PAGEDOWN"},
    {110, "INSERT"},
    {111, "DELETE"},
    {112, "MACRO"},
    {113, "MUTE"},
    {114, "VOLUMEDOWN"},
    {115, "VOLUMEUP"},
    {116, "POWER"},
    {117, "KPEQUAL"},
    {118, "KPPLUSMINUS"},
    {119, "PAUSE"},
    {120, "SCALE"},
    {121, "KPCOMMA"},
    {122, "HANGEUL"},
    {123, "HANJA"},
    {124, "YEN"},
    {125, "LEFTMETA"}};


void catchKeyPressUntilESC(int &newSd)
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
                    temp += "Key " + MAP[ev.code] + " was pressed.";
                    
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