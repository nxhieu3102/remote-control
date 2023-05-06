#pragma once
#include "raylib.h"
#include "../FUNCTION/clientFunction.h"
class ClientGUI{
private:
    clientFunction* cf = NULL;
public:
    ClientGUI();
    ~ClientGUI();
    void drawLoginRoom();
    void drawMenuRoom();

    void DrawMenuItem(Rectangle rect, const char* text, Color buttonColor = GRAY);
    bool IsMenuItemPressed(Rectangle rect);

    static const int HEIGHT = 450;
    static const int WIDTH = 800;    
};