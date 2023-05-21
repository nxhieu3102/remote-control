#include "ListApp.h"

void ClientGUI::drawListAppRoom() {
    while (!WindowShouldClose()) {
            Color buttonColor = RED;
            BeginDrawing();
                ClearBackground(WHITE);
                DrawTexture(background, 0, 0, WHITE);

                for(int i = 0 ; i < 3 ; i++)
                    DrawMenuItem(MENU_BUTTON[i].rect, MENU_BUTTON[i].label, buttonColor, 20);

            EndDrawing();
        }
}