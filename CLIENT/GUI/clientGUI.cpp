#include "clientGUI.h"

void ClientGUI::DrawMenuItem(Rectangle rect, const char* text, Color buttonColor, int fontSize){
    DrawRectangleRec(rect, buttonColor);
    DrawText(text, rect.x + 10, rect.y + 10, fontSize, LIGHTGRAY);
}

bool ClientGUI::IsMenuItemPressed(Rectangle rect) {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void ClientGUI::start(){
    InitWindow(ClientGUI::WIDTH, ClientGUI::HEIGHT, "Login Room");
    SetTargetFPS(60);

    Image BACKGROUND = LoadImage("background.png");
    ImageResize(&BACKGROUND, ClientGUI::WIDTH, ClientGUI::HEIGHT);
    background = LoadTextureFromImage(BACKGROUND);

    drawLoginRoom();

    if(doesLoginSuccess){
        drawMenuRoom();
        while(true){
            if(backToMenu)
                drawMenuRoom();
            if(exit)
                break;
        }
    }
}

void ClientGUI::stop(){
    CloseWindow(); 
}

ClientGUI::ClientGUI(){

}

ClientGUI::~ClientGUI(){
    delete cf;
}