#pragma once
#include "raylib.h"
#include "../FUNCTION/clientFunction.h"
#include <string>

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

class ClientGUI{
private:
    clientFunction* cf = NULL;
    Texture2D background;

    button MENU_BUTTON[5] = {
        button("Capture Screen", (Rectangle){100, 100, 200, 50}),
        button("List all app", (Rectangle){ 100, 200, 200, 50 }),
        button("List all process", (Rectangle){ 500, 200, 200, 50 }),
        button("Key logger", (Rectangle){ 500, 100, 200, 50 }),
        button("Tree folder", (Rectangle){ 300, 300, 200, 50 })
    };

public:
    ClientGUI();
    ~ClientGUI();

    void start();
    void stop();

    void drawLoginRoom();
    void drawMenuRoom();

    void DrawMenuItem(Rectangle rect, const char* text, Color buttonColor = GRAY, int fontSize = 30);
    bool IsMenuItemPressed(Rectangle rect);

    static const int HEIGHT = 450;
    static const int WIDTH = 800;    
};