#include "raylib.h"

#define MAX_COLORS_COUNT 7          

void Cleaning_Button(bool btnAction, int btnState, Vector2 mousePos, Rectangle btnBoundsCleaning, Rectangle colorsRecs, int colorMouseHover, RenderTexture2D target)
{
    if (IsKeyPressed(KEY_C))
    {
        // Clear field for painting
        BeginTextureMode(target);
          ClearBackground(WHITE);
        EndTextureMode();
    }

    if (CheckCollisionPointRec(mousePos, btnBoundsCleaning))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        BeginTextureMode(target);
          ClearBackground(WHITE);
        EndTextureMode();
        btnAction = false;
        btnState = 0;
    }
}

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "paint");

    Texture2D buttonCleaning = LoadTexture("CleanButton.png");

    float frameHeight = (float)buttonCleaning.height;
    Rectangle sourceRecCleaning = { 0, 0, (float)buttonCleaning.width, frameHeight };
    Rectangle btnBoundsCleaning = { 275, 0, (float)buttonCleaning.width, frameHeight };
    int btnState = 0;
    bool btnAction = false;

    Color colors[MAX_COLORS_COUNT] = {BLACK, WHITE, RED,  BLUE, YELLOW, GREEN, PINK};
    Rectangle colorsRecs[MAX_COLORS_COUNT] = { 0 };

    for (int i = 0; i < MAX_COLORS_COUNT; i++)
    {
        colorsRecs[i].x = 10 + 30.0f * i + 10 * i;
        colorsRecs[i].y = 10;
        colorsRecs[i].width = 30;
        colorsRecs[i].height = 30;
    }

    int colorSelected = 0;
    int colorMouseHover = 0;
    float brushSize = 5.0f;
    bool mouseWasPressed = false;

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    BeginTextureMode(target);
    ClearBackground(WHITE);
    EndTextureMode();

    SetTargetFPS(1200);              
    while (!WindowShouldClose())
    {
        btnAction = false;

        Vector2 mousePos = GetMousePosition();

        Cleaning_Button(btnAction, btnState, mousePos, btnBoundsCleaning, colorsRecs[6], colorMouseHover, target);

        // Choose color 
        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            if (CheckCollisionPointRec(mousePos, colorsRecs[i]))
            {
                colorMouseHover = i;
                break;
            }
            else colorMouseHover = -1; 
        }

        if ((colorMouseHover >= 0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            colorSelected = colorMouseHover;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            
            BeginTextureMode(target);
            if (mousePos.y > 50) 
                DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[colorSelected]);
            EndTextureMode();
        }
       
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);

        // Draw gray circle 
        if (mousePos.y > 50)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawCircleLines((int)mousePos.x, (int)mousePos.y, brushSize + 5.0f, GRAY);
            else 
                DrawCircle(GetMouseX(), GetMouseY(), brushSize + 5.0f, colors[colorSelected]);
        }

        DrawRectangle(0, 0, GetScreenWidth(), 50, Fade(LIGHTGRAY, 0.8f)); // Draw top panel

        // Draw color selection rectangles
        for (int i = 0; i < MAX_COLORS_COUNT; i++) 
            DrawRectangleRec(colorsRecs[i], colors[i]);

        if (colorMouseHover >= 0) 
            DrawRectangleRec(colorsRecs[colorMouseHover], Fade(LIGHTGRAY, 0.8f));

        

        //frame of the selected color
        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            DrawRectangleLinesEx((Rectangle) { colorsRecs[i].x - 2, colorsRecs[i].y - 2, colorsRecs[i].width + 4, colorsRecs[i].height + 4 }, 3, Fade(BLACK, 0.5f));
        }
        DrawRectangleLinesEx((Rectangle) {colorsRecs[colorSelected].x - 2,   colorsRecs[colorSelected].y - 2,   colorsRecs[colorSelected].width + 4,   colorsRecs[colorSelected].height + 4}, 3, GOLD);

        DrawTextureRec(buttonCleaning, sourceRecCleaning, (Vector2) { btnBoundsCleaning.x, btnBoundsCleaning.y }, WHITE);

        if (mousePos.x >= btnBoundsCleaning.x && mousePos.y <= btnBoundsCleaning.y + btnBoundsCleaning.height && mousePos.x <= btnBoundsCleaning.x + btnBoundsCleaning.width && mousePos.y > btnBoundsCleaning.y)
            DrawRectangleRec(btnBoundsCleaning, Fade(LIGHTGRAY, 0.4f));

        EndDrawing();
    }

    UnloadRenderTexture(target);  
    CloseWindow(); 
    return 0;
}