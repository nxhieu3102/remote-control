#include "Menu.h"

void ClientGUI::drawMenuRoom(){   
    bool doesPressed = false;
    cout << doesPressed << "\n";

    while (!WindowShouldClose()) {
    	Color buttonColor = RED;
        
        for(int i = 0 ; i < 5 ; i++){
            if(IsMenuItemPressed(MENU_BUTTON[i].rect)){
                if(strcmp("Capture Screen", MENU_BUTTON[i].label) == 0){
                    roomCaptureScreen = true;
                    doesPressed = true;
                    cout << "Capture Screen\n";
                }
                if(strcmp("List all app", MENU_BUTTON[i].label) == 0){
                    roomListApp = true;
                    doesPressed = true;
                    cout << "List all app" << "\n";
                }
                if(strcmp("List all process", MENU_BUTTON[i].label) == 0){
                    roomListProcess = true;
                    doesPressed = true;
                    cout << "List all process" << "\n";
                }
                if(strcmp("Key logger", MENU_BUTTON[i].label) == 0){
                    roomKeyLogger = true;
                    doesPressed = true;
                    cout << "Key logger" << "\n";
                }
                if(strcmp("Tree folder", MENU_BUTTON[i].label) == 0){
                    roomTreeFolder = true;
                    doesPressed = true;
                    cout << "press tree folder" << "\n";
                }
            }
        }
        
        if(doesPressed) {
            backToMenu = false;
            break;
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(background, 0, 0, WHITE);

            for(int i = 0 ; i < 5 ; i++)
                DrawMenuItem(MENU_BUTTON[i].rect, MENU_BUTTON[i].label, buttonColor, 20);

        EndDrawing();
    }
}