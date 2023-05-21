#include "Login.h"


bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

void ClientGUI::drawLoginRoom(){
    button buttonLogin("LOGIN", (Rectangle){ 300, 250, 200, 50 });
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        bool doesHaveMouseOn = false;
        for(int i = 0 ; i < 2 ; i++){
            if(input::doesMouseOn(INPUT_LOGIN[i].box))
                INPUT_LOGIN[i].mouseOn = true, doesHaveMouseOn = true;
            else INPUT_LOGIN[i].mouseOn = false;

            if(INPUT_LOGIN[i].mouseOn){
                SetMouseCursor(MOUSE_CURSOR_IBEAM);

                // Get char pressed (unicode character) on the queue
                int key = GetCharPressed();
                int keyPressed = GetKeyPressed();
                // Check if more characters have been pressed on the same frame
                while (key > 0)
                {   
                    
                    // NOTE: Only allow keys in range [32..125]

                    if ((key >= 32) && (key <= 125) && (INPUT_LOGIN[i].letterCount < input::MAX_INPUT_CHARS))
                    {
                        INPUT_LOGIN[i].inputValue[INPUT_LOGIN[i].letterCount] = (char)key;
                        INPUT_LOGIN[i].inputValue[INPUT_LOGIN[i].letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                        INPUT_LOGIN[i].letterCount++;
                    }

                    key = GetCharPressed();  // Check next character in the queue
                }

                if (keyPressed == 259)
                {   
                    INPUT_LOGIN[i].letterCount--;
                    if (INPUT_LOGIN[i].letterCount < 0) INPUT_LOGIN[i].letterCount = 0;
                    INPUT_LOGIN[i].inputValue[INPUT_LOGIN[i].letterCount] = '\0';
                }

                INPUT_LOGIN[i].framesCounter++;

            }else{
                INPUT_LOGIN[i].framesCounter = 0;
            }
        }

        if(!doesHaveMouseOn)
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        if (IsMenuItemPressed(buttonLogin.rect)) {
            bool flag = false;
            cf = new clientFunction(INPUT_LOGIN[0].inputValue, INPUT_LOGIN[1].inputValue, flag);
            if(flag) {
                doesLoginSuccess = true;
                break;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(background, 0, 0, WHITE);
            DrawText("IP", 100, 110, 40, GRAY);
            DrawText("PORT", 475, 110, 40, GRAY);
            
            for(int i = 0 ; i < 2 ; i++){
                DrawRectangleRec(INPUT_LOGIN[i].box, LIGHTGRAY);
                if(INPUT_LOGIN[i].mouseOn){
                    DrawRectangleLines((int)INPUT_LOGIN[i].box.x, (int)INPUT_LOGIN[i].box.y, (int)INPUT_LOGIN[i].box.width, (int)INPUT_LOGIN[i].box.height, RED);
                }else DrawRectangleLines((int)INPUT_LOGIN[i].box.x, (int)INPUT_LOGIN[i].box.y, (int)INPUT_LOGIN[i].box.width, (int)INPUT_LOGIN[i].box.height, DARKGRAY);
                DrawText(INPUT_LOGIN[i].inputValue, (int)INPUT_LOGIN[i].box.x + 5, (int)INPUT_LOGIN[i].box.y + 10, 30, MAROON);
            }

            DrawMenuItem(buttonLogin.rect, buttonLogin.label);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}