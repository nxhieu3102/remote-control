#include "CaptureScreen.h"

#define IMAGE_WIDTH 1200
#define IMAGE_HEIGHT 675

void ClientGUI::drawCaptureScreenRoom() {
    string filename = cf->CaptureScreen();
    const button back_button = button("BACK", (Rectangle){1350, 0, 150, 50});

    Image capture = LoadImage(filename.c_str());
    ImageResize(&capture, IMAGE_WIDTH, IMAGE_HEIGHT);
    Texture2D texture_image = LoadTextureFromImage(capture);

    while (!WindowShouldClose()) {
        if (IsMenuItemPressed(back_button.rect)) {
            cout << "press\n";
            backToMenu = true;
            roomCaptureScreen = false;
            break;
        }

        BeginDrawing();
        {
            ClearBackground(WHITE);
            DrawTexture(background, 0, 0, WHITE);
            DrawTexture(texture_image, 50, 50, WHITE);
            DrawMenuItem(back_button.rect, back_button.label, RED, 20);
        }
        EndDrawing();
    }

}