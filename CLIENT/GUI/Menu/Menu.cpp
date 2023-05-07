#include "Menu.h"

void ClientGUI::drawMenuRoom(){   
    while (!WindowShouldClose()) {
    	Color buttonColor = RED;
        Color pressedButonColor = RED;
        int pressedButton = -1;
        
        for(int i = 0 ; i < 5 ; i++){
            if(IsMenuItemPressed(MENU_BUTTON[i].rect))
                pressedButton = i;
        }

        
        if(pressedButton != -1){
            pressedButonColor = GRAY;
        }

        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(background, 0, 0, WHITE);

            for(int i = 0 ; i < 5 ; i++)
                DrawMenuItem(MENU_BUTTON[i].rect, MENU_BUTTON[i].label, buttonColor, 20);

        EndDrawing();
    }
}