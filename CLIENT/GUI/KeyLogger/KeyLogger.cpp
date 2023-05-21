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
    const Font font = LoadFont("pixelplay.png");
    const button back_button = button("BACK", (Rectangle){1350, 0, 150, 50});

    char msg[50];
	strcpy(msg, "4");
	msg[strlen(msg)] = '\0';
	send(client_Sd, (char *)&msg, strlen(msg), 0);
    int byteRecv = 0;
    char res[1000];
    res[0] = '\0';

    while (!WindowShouldClose()) {

        scrollOffset -= GetMouseWheelMove() * SCROLL_SPEED;
        if (IsMenuItemPressed(back_button.rect)) {
            cout << "press\n";
            backToMenu = true;
            roomKeyLogger = false;

            char msg[10];
            strcpy(msg, "exit");
            msg[strlen(msg)] = '\0';
            

            send(client_Sd, (char *)&msg, strlen(msg), 0);
            
            char temp[100];
            memset(temp, 0, sizeof(temp));
            int bytesReceived = recv(client_Sd, (char *)&temp, sizeof(temp), 0);
            break;
        }

        if(strlen(msg) > 5){
            strcat(res, msg);
            strcat(res, "\n");
        }

        BeginDrawing();
        {
            ClearBackground(WHITE);
            DrawTexture(background, 0, 0, WHITE);
            DrawRectangleRec(textRectangle, LIGHTGRAY);
            BeginScissorMode(textRectangle.x, textRectangle.y, textRectangle.width, textRectangle.height);
            DrawTextEx(GetFontDefault(), res, (Vector2){textRectangle.x + 10, textRectangle.y - scrollOffset}, 20, 3, BLACK);
            EndScissorMode();
            DrawMenuItem(back_button.rect, back_button.label, RED, 20);
        }
        EndDrawing();

        memset(&msg, 0, sizeof(msg));

        // Set up the file descriptor set for select()
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(client_Sd, &readfds);

        // Set up the timeout for select() to 1 second
        timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        // Use select() to wait for data or timeout
        int selectResult = select(client_Sd + 1, &readfds, NULL, NULL, &timeout);

        if (selectResult == -1) {
            // Error occurred in select()
            perror("select");
            break;
        } else if (selectResult == 0) {
            // Timeout occurred
            // Perform actions when the recv() takes longer than 1 second
            // ...

            continue; // Skip to the next iteration of the loop
        }

        byteRecv = recv(client_Sd, (char *)&msg, sizeof(msg), 0); // receive message

        if (byteRecv <= 0 || stopListening == 1) {
            cout << "Stop listen from the Server\n";
            kt = 0;
            return;
        }

        fflush(stdin);
        }

}