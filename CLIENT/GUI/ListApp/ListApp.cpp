#include "ListApp.h"

#define RECTANGLE_WIDTH 800
#define RECTANGLE_HEIGHT 800
#define SCROLL_SPEED 50

void ClientGUI::drawListAppRoom() {
    string res = cf->listInstalledProgram();
    const char *res_char = res.c_str();

    input start_app_input = input((Rectangle){ 1000, 150, 225, 50 }, "START APP NAME");
    input end_app_input = input((Rectangle){ 1000, 250, 225, 50 }, "END APP NAME");

    const button start_app_button = button("START", (Rectangle){1250, 150, 150, 50});
    const button end_app_button = button("END", (Rectangle){1250, 250, 150, 50});

    bool doesMouseOnStartInput = false;
    bool doesMouseOnEndInput = false;

    bool doesHaveMouseOn = false;

    int scrollOffset = 0;

    int maxScrollOffset = MeasureText(res_char, 40);
    const Rectangle textRectangle = { 50, 50, RECTANGLE_WIDTH, RECTANGLE_HEIGHT };
    const Font font = LoadFont("jupiter_crash.png");
    

    const button back_button = button("BACK", (Rectangle){1450, 0, 150, 50});

     while (!WindowShouldClose()) {
        if(input::doesMouseOn(start_app_input.box)) doesMouseOnStartInput = true, doesHaveMouseOn = true;
        else doesMouseOnStartInput = false;

        if(input::doesMouseOn(end_app_input.box)) doesMouseOnEndInput = true, doesHaveMouseOn = true;
        else doesMouseOnEndInput = false;

        if(doesMouseOnStartInput){
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {   
                
                // NOTE: Only allow keys in range [32..125]

                if ((key >= 32) && (key <= 125) && (start_app_input.letterCount < input::MAX_INPUT_CHARS))
                {
                    start_app_input.inputValue[start_app_input.letterCount] = (char)key;
                    start_app_input.inputValue[start_app_input.letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                    start_app_input.letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyDown(KEY_BACKSPACE))
            {   
                start_app_input.letterCount--;
                if (start_app_input.letterCount < 0) start_app_input.letterCount = 0;
                start_app_input.inputValue[start_app_input.letterCount] = '\0';
            }

            start_app_input.framesCounter++;

        }else{
            start_app_input.framesCounter = 0;
        }
        if(doesMouseOnEndInput){
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {   
                
                // NOTE: Only allow keys in range [32..125]

                if ((key >= 32) && (key <= 125) && (end_app_input.letterCount < input::MAX_INPUT_CHARS))
                {
                    end_app_input.inputValue[end_app_input.letterCount] = (char)key;
                    end_app_input.inputValue[end_app_input.letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                    end_app_input.letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyDown(KEY_BACKSPACE))
            {   
                end_app_input.letterCount--;
                if (end_app_input.letterCount < 0) end_app_input.letterCount = 0;
                end_app_input.inputValue[end_app_input.letterCount] = '\0';
            }

            end_app_input.framesCounter++;

        }else{
            end_app_input.framesCounter = 0;
        }

        if(!doesMouseOnEndInput && !doesMouseOnStartInput)
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            
        scrollOffset -= GetMouseWheelMove() * SCROLL_SPEED;

        if(IsMenuItemPressed(back_button.rect)){
            cout << "press" << "\n";
            backToMenu = true;
            roomListApp = false;
            break;
        }

        if(IsMenuItemPressed(start_app_button.rect)){
            cout << start_app_input.inputValue << "\n";
            cf->start_stop_app(start_app_input.inputValue, 1);
        }

        if(IsMenuItemPressed(end_app_button.rect)){
            cf->start_stop_app(end_app_input.inputValue, 6);
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
            DrawMenuItem(start_app_button.rect, start_app_button.label, RED, 20);
            DrawMenuItem(end_app_button.rect, end_app_button.label, RED, 20);
            DrawRectangleRec(start_app_input.box, LIGHTGRAY);
            DrawRectangleRec(end_app_input.box, LIGHTGRAY);

            if(doesMouseOnEndInput){
                DrawRectangleLines((int)end_app_input.box.x, (int)end_app_input.box.y, (int)end_app_input.box.width, (int)end_app_input.box.height, RED);
            }else DrawRectangleLines((int)end_app_input.box.x, (int)end_app_input.box.y, (int)end_app_input.box.width, (int)end_app_input.box.height, DARKGRAY);
            DrawText(end_app_input.inputValue, (int)end_app_input.box.x + 5, (int)end_app_input.box.y + 10, 30, MAROON);

            if(doesMouseOnStartInput){
                DrawRectangleLines((int)start_app_input.box.x, (int)start_app_input.box.y, (int)start_app_input.box.width, (int)start_app_input.box.height, RED);
            }else DrawRectangleLines((int)start_app_input.box.x, (int)start_app_input.box.y, (int)start_app_input.box.width, (int)start_app_input.box.height, DARKGRAY);
            DrawText(start_app_input.inputValue, (int)start_app_input.box.x + 5, (int)start_app_input.box.y + 10, 30, MAROON);

            
        }
        EndDrawing();
    }
}

