#pragma once
#include "raylib.h"
#include "../FUNCTION/clientFunction.h"
#include <string>
#include <string.h>
#include <sys/select.h>

class button;
class input;
class ClientGUI;

class button {
public:

    button(const char* _label, Rectangle _rect) {
        label = new char[strlen(_label) + 1];
        strcpy(label, _label);

        rect = _rect;
    }



    ~button() {
        delete label;
    }

    char* label;
    Rectangle rect;
};

class input {
public:
    input(){}

    input(Rectangle _box, const char* _label){
        box = _box;
        mouseOn = false;
        framesCounter = 0;
        label = new char[strlen(_label) + 1];
        strcpy(label, _label);
        inputValue = new char[MAX_INPUT_CHARS + 1]{'\0'};
        letterCount = 0;
    }

    Rectangle box;
    bool mouseOn; 
    int framesCounter;
    char* label;
    char* inputValue;
    int letterCount;

    static const int MAX_INPUT_CHARS = 15;
    static bool doesMouseOn(Rectangle _box){
        return CheckCollisionPointRec(GetMousePosition(), _box);
    }
}; 

class ClientGUI{
private:
    clientFunction* cf = NULL;
    Texture2D background;
    bool doesLoginSuccess = false;

    bool backToMenu = false;
    
    bool roomListApp = false;
    bool roomListProcess = false;
    bool roomKeyLogger = false;
    bool roomTreeFolder = false;
    bool roomCaptureScreen = false;

    bool exit = false;

    
    button MENU_BUTTON[5] = {
        button("Capture Screen", (Rectangle){100, 100, 250, 50}),
        button("List all app", (Rectangle){ 100, 200, 250, 50 }),
        button("List all process", (Rectangle){ 500, 200, 250, 50 }),
        button("Key logger", (Rectangle){ 500, 100, 250, 50 }),
        button("Tree folder", (Rectangle){ 300, 300, 250, 50 })
    };

    input INPUT_LOGIN[2] = {
        input((Rectangle){ 100, 150, 225, 50 }, "IP"),
        input((Rectangle){ 475, 150, 225, 50 }, "PORT")
    };

public:

    ClientGUI();
    ~ClientGUI();

    void start();
    void stop();

    void drawLoginRoom();
    void drawMenuRoom();

    void drawListAppRoom();
    void drawListProcessRoom();
    void drawTreeFolderRoom();
    void drawKeyLoggerRoom();
    void drawCaptureScreenRoom();

    void DrawMenuItem(Rectangle rect, const char* text, Color buttonColor = GRAY, int fontSize = 30);
    bool IsMenuItemPressed(Rectangle rect);

    static const int HEIGHT = 700;
    static const int WIDTH = 1500;    
};