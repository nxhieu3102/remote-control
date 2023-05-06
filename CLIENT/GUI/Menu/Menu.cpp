#include "Menu.h"

void ClientGUI::drawMenuRoom(){
    InitWindow(800, 450, "REMOTE CONTROL");
    
    SetTargetFPS(60);
    
    Image BACKGROUND = LoadImage("background.png");
    ImageResize(&BACKGROUND, 800, 450);
    Texture2D texture = LoadTextureFromImage(BACKGROUND);
    
    Rectangle buttonCaptureScreen = { 100, 100, 200, 50 };
    const char* buttonCaptureScreenText = "Capture Screen";

    Rectangle buttonListAllApp = { 100, 200, 200, 50 };
    const char* buttonListAllAppText = "List all app";

    Rectangle buttonListAllProccess = { 500, 200, 200, 50 };
    const char* buttonListAllProcessText = "List all process";

    Rectangle buttonKeyLogger = { 500, 100, 200, 50 };
    const char* buttonKeyLoggerText = "Key logger";

    Rectangle buttonTreeFolder = { 300, 300, 200, 50 };
    const char* buttonTreeFolderText = "Tree folder";


    while (!WindowShouldClose()) {
    	Color buttonColor = RED;
        Color pressedButonColor = RED;
        int pressedButton = -1;
        if (IsMenuItemPressed(buttonCaptureScreen)) {
            pressedButton = 0;
        }

        if (IsMenuItemPressed(buttonListAllApp)) {
            pressedButton = 1;
        }

        if (IsMenuItemPressed(buttonListAllProccess)) {
            pressedButton = 2;
        }

        if (IsMenuItemPressed(buttonKeyLogger)) {
            pressedButton = 3;
        }

        if (IsMenuItemPressed(buttonTreeFolder)) {
            pressedButton = 4;
        }

        if(pressedButton != -1){
            pressedButonColor = GRAY;
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(texture, 0, 0, WHITE);

            DrawMenuItem(buttonCaptureScreen, buttonCaptureScreenText, pressedButton == 0 ? pressedButonColor : buttonColor);
            DrawMenuItem(buttonListAllApp, buttonListAllAppText, pressedButton == 1 ? pressedButonColor : buttonColor);
            DrawMenuItem(buttonListAllProccess, buttonListAllProcessText, pressedButton == 2 ? pressedButonColor : buttonColor);
            DrawMenuItem(buttonKeyLogger, buttonKeyLoggerText, pressedButton == 3 ? pressedButonColor : buttonColor);
            DrawMenuItem(buttonTreeFolder, buttonTreeFolderText, pressedButton == 4 ? pressedButonColor : buttonColor);

        EndDrawing();
    }

    CloseWindow();
}