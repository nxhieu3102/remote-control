#include "Menu.h"

void ClientGUI::drawMenuRoom(){   
    while (!WindowShouldClose()) {
    	Color buttonColor = RED;
        
        for(int i = 0 ; i < 5 ; i++){
            if(IsMenuItemPressed(MENU_BUTTON[i].rect)){
                if(MENU_BUTTON[i].callback != NULL)
                    MENU_BUTTON[i].callback(*this);
            }
        }
        


        BeginDrawing();
            ClearBackground(WHITE);
            DrawTexture(background, 0, 0, WHITE);

            for(int i = 0 ; i < 5 ; i++)
                DrawMenuItem(MENU_BUTTON[i].rect, MENU_BUTTON[i].label, buttonColor, 20);

        EndDrawing();
    }
}