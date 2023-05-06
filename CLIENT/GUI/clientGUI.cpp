#include "clientGUI.h"

void ClientGUI::DrawMenuItem(Rectangle rect, const char* text, Color buttonColor){
    DrawRectangleRec(rect, buttonColor);
    DrawText(text, rect.x + 10, rect.y + 10, 30, LIGHTGRAY);
}

bool ClientGUI::IsMenuItemPressed(Rectangle rect) {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

ClientGUI::ClientGUI(){

}

ClientGUI::~ClientGUI(){
    delete cf;
}