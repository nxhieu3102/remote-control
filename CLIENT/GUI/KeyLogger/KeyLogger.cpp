#include "KeyLogger.h"

#define RECTANGLE_WIDTH 800
#define RECTANGLE_HEIGHT 800
#define SCROLL_SPEED 50

void ClientGUI::drawKeyLoggerRoom() {

    cout << "Draw key logger room\n";
    int client_Sd = cf->clientSd;
    bool kt = 1, stopListening = 0;

    cout << client_Sd << "\n";
    int scrollOffset = 0;
    const Rectangle textRectangle = { 50, 50, RECTANGLE_WIDTH, RECTANGLE_HEIGHT };
    const Font font = LoadFont("jupiter_crash.png");
    const button back_button = button("BACK", (Rectangle){1350, 0, 250, 50});

     while (!WindowShouldClose()) {
        char msg[50];
        memset(&msg, 0, sizeof(msg));

        int byteRecv = recv(client_Sd, (char *)&msg, sizeof(msg), 0); // receive message
        if (byteRecv <= 0 || stopListening == 1)
        {
            cout << "Stop listen from the Server\n";
            kt = 0;
            return;
        }

        cout << msg << "\n";
        fflush(stdin);
        fflush(stdin);

        scrollOffset -= GetMouseWheelMove() * SCROLL_SPEED;

        if(IsMenuItemPressed(back_button.rect)){
            backToMenu = true;
            roomKeyLogger = false;
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
            // DrawTextEx(font, msg, (Vector2){ textRectangle.x + 10, textRectangle.y - scrollOffset} ,
            //            20, 3, BLACK);
            
            // Disable the scissor mode to draw outside the rectangle
            EndScissorMode();
            DrawMenuItem(back_button.rect, back_button.label, RED, 20);
        }
        EndDrawing();
    }

}