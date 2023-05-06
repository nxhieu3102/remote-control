#include "Login.h"

#define MAX_INPUT_CHARS     50

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}

void ClientGUI::drawLoginRoom(){

    const int screenWidth = ClientGUI::WIDTH;
    const int screenHeight = ClientGUI::HEIGHT;

    InitWindow(screenWidth, screenHeight, "Login Room");
    SetTargetFPS(60);               // Set our game to run at 10 frames-per-second

    char IP[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    char PORT[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    
    int letterCountIP = 0;
    int letterCountPORT = 0;

    Rectangle IPBox = { 100, 150, 225, 50 };
    Rectangle PORTBox = { 475, 150, 225, 50 };

    bool mouseOnIPBox = false;
    bool mouseOnPORTBox = false;

    int framesCounterIP = 0;
    int framesCounterPORT = 0;


    Rectangle buttonLogin = { 300, 250, 200, 50 };
    const char* buttonLoginText = "LOGIN";


    Image BACKGROUND = LoadImage("background.png");
    ImageResize(&BACKGROUND, 800, 450);
    Texture2D texture = LoadTextureFromImage(BACKGROUND);

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), IPBox)) mouseOnIPBox = true;
        else mouseOnIPBox = false;

        if (CheckCollisionPointRec(GetMousePosition(), PORTBox)) mouseOnPORTBox = true;
        else mouseOnPORTBox = false;

        if (mouseOnIPBox)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {   
                cout << key << endl;
                // NOTE: Only allow keys in range [32..125]
                
                if ((key >= 32) && (key <= 125) && (letterCountIP < MAX_INPUT_CHARS))
                {
                    IP[letterCountIP] = (char)key;
                    IP[letterCountIP+1] = '\0'; // Add null terminator at the end of the string.
                    letterCountIP++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {   
                cout<<"-----------xoa'----------";
                letterCountIP--;
                if (letterCountIP < 0) letterCountIP = 0;
                IP[letterCountIP] = '\0';
            }
        }
        else if (mouseOnPORTBox)
        {
            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCountPORT < MAX_INPUT_CHARS))
                {
                    PORT[letterCountPORT] = (char)key;
                    PORT[letterCountPORT+1] = '\0'; // Add null terminator at the end of the string.
                    letterCountPORT++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCountPORT--;
                if (letterCountPORT < 0) letterCountPORT = 0;
                PORT[letterCountPORT] = '\0';
            }
        }

        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnIPBox) framesCounterIP++;
        else framesCounterIP = 0;

        if (mouseOnPORTBox) framesCounterPORT++;
        else framesCounterPORT = 0;

        if (IsMenuItemPressed(buttonLogin)) {
            bool flag = false;
            cf = new clientFunction(IP, PORT, flag);
            if(flag) {
                break;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTexture(texture, 0, 0, WHITE);
            DrawText("IP", 100, 110, 40, GRAY);
            DrawText("PORT", 475, 110, 40, GRAY);
            
            DrawRectangleRec(IPBox, LIGHTGRAY);
            DrawRectangleRec(PORTBox, LIGHTGRAY);

            if (mouseOnIPBox) DrawRectangleLines((int)IPBox.x, (int)IPBox.y, (int)IPBox.width, (int)IPBox.height, RED);
            else DrawRectangleLines((int)IPBox.x, (int)IPBox.y, (int)IPBox.width, (int)IPBox.height, DARKGRAY);

            if (mouseOnPORTBox) DrawRectangleLines((int)PORTBox.x, (int)PORTBox.y, (int)PORTBox.width, (int)PORTBox.height, RED);
            else DrawRectangleLines((int)PORTBox.x, (int)PORTBox.y, (int)PORTBox.width, (int)PORTBox.height, DARKGRAY);

            DrawText(IP, (int)IPBox.x + 5, (int)IPBox.y + 10, 30, MAROON);
            DrawText(PORT, (int)PORTBox.x + 5, (int)PORTBox.y + 10, 30, MAROON);

            DrawMenuItem(buttonLogin, buttonLoginText);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); 
    drawMenuRoom();
           // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}