#include "ListApp.h"

#define RECTANGLE_WIDTH 800
#define RECTANGLE_HEIGHT 800
#define SCROLL_SPEED 50

void ClientGUI::drawListAppRoom() {
    string res = cf->listInstalledProgram();

    const char *res_char = res.c_str();
    int scrollOffset = 0;
    int maxScrollOffset = MeasureText(res_char, 40);
    const Rectangle textRectangle = { 50, 50, RECTANGLE_WIDTH, RECTANGLE_HEIGHT };
    const Font font = LoadFont("jupiter_crash.png");
    

    const button back_button = button("BACK", (Rectangle){1350, 0, 250, 50});

     while (!WindowShouldClose()) {
        scrollOffset -= GetMouseWheelMove() * SCROLL_SPEED;

        if(IsMenuItemPressed(back_button.rect)){
            cout << "press" << "\n";
            backToMenu = true;
            roomListApp = false;
            break;
        }

        BeginDrawing();
        {
            ClearBackground(WHITE);
            DrawTexture(background, 0, 0, WHITE);

            // Draw the rectangle
            DrawRectangleRec(textRectangle, LIGHTGRAY);

            // Set the clipping rectangle to only render within the text rectangle
            BeginScissorMode(textRectangle.x, textRectangle.y, textRectangle.width, textRectangle.height);
            
            // Draw the text with the scrolling offset
            DrawTextEx(font, res_char, (Vector2){ textRectangle.x + 10, textRectangle.y - scrollOffset },
                       40, 3, BLACK);
            
            // Disable the scissor mode to draw outside the rectangle
            EndScissorMode();
            DrawMenuItem(back_button.rect, back_button.label, RED, 20);
        }
        EndDrawing();
    }
}

