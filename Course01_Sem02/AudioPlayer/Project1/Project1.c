#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <locale.h>
#include <string.h>
#include"Header.h"

int main(void)
{
    setlocale(LC_ALL, "ru-RU");
    AudioList();

    const int screenWidth = 850;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Audio player");
    InitAudioDevice();

    Music music = LoadMusicStream("resoursesMusic/OverworldDay.mp3");

    Texture2D buttonPlay = LoadTexture("resoursesTexture/buttonPlay.png");
    Texture2D buttonPause = LoadTexture("resoursesTexture/buttonPause.png");
    Texture2D buttonRightRewind = LoadTexture("resoursesTexture/buttonRightRewind.png");
    Texture2D buttonLeftRewind = LoadTexture("resoursesTexture/buttonLeftRewind.png");
    Texture2D buttonLouder = LoadTexture("resoursesTexture/buttonLouder.png");
    Texture2D buttonQuiet = LoadTexture("resoursesTexture/buttonQuiet.png");
    Texture2D buttonSlower = LoadTexture("resoursesTexture/buttonSlower.png");
    Texture2D buttonFaster = LoadTexture("resoursesTexture/buttonFaster.png");

    Texture2D buttonBar1 = LoadTexture("resoursesTexture/bar1.png");

    PlayMusicStream(music);
    SetMusicVolume(music, 0.5);

    float timePlayed = 0.0f, volumeFlag = 0.5, speedFlag = 1.0f;
    bool pause = false;

    // Define frame rectangle for drawing
    float frameHeight = (float)buttonPlay.height;
    Rectangle sourceRecPlay = { 0, 0, (float)buttonPlay.width, frameHeight };
    Rectangle sourceRecPause = { 0, 0, (float)buttonPause.width, frameHeight };
    Rectangle sourceRecRightRewind = { 0, 0, (float)buttonRightRewind.width, frameHeight };
    Rectangle sourceRecLeftRewind = { 0, 0, (float)buttonLeftRewind.width, frameHeight };
    Rectangle sourceRecLouder = { 0, 0, (float)buttonLouder.width, frameHeight };
    Rectangle sourceRecQuiet = { 0, 0, (float)buttonQuiet.width, frameHeight };
    Rectangle sourceRecSlower = { 0, 0, (float)buttonSlower.width, frameHeight };
    Rectangle sourceRecFaster = { 0, 0, (float)buttonFaster.width, frameHeight };

    Rectangle sourceRecBar1 = { 0, 0, (float)buttonBar1.width, buttonBar1.height };

    // Define field rectangle for drawing
    Rectangle btnBoundsPlay = { 150, 200, (float)buttonPlay.width, frameHeight };
    Rectangle btnBoundsPause = { 250, 200, (float)buttonPause.width, frameHeight };
    Rectangle btnBoundsLeftRewind = { 350, 200, (float)buttonLeftRewind.width, frameHeight };
    Rectangle btnBoundsRightRewind = { 450, 200, (float)buttonRightRewind.width, frameHeight };
    Rectangle btnBoundsSlower = { 550, 200, (float)buttonSlower.width, frameHeight };
    Rectangle btnBoundsFaster = { 650, 200, (float)buttonFaster.width, frameHeight };
    Rectangle btnBoundsLouder = { 645, 330, (float)buttonLouder.width, frameHeight };
    Rectangle btnBoundsQuiet = { 100, 330, (float)buttonQuiet.width, frameHeight };

    Rectangle btnBoundsBar1 = { 200, 150, (float)buttonBar1.width, buttonBar1.height };

    int btnState = 0, volumeLine = 200;              // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated

    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);

    short i = 0;

    while (!WindowShouldClose())
    {

        mousePoint = GetMousePosition();
        btnAction = false;
        ///  Buttons for some functions

        PlayButton(btnAction, btnState, mousePoint, btnBoundsPlay, music);

        PauseButton(btnAction, btnState, mousePoint, btnBoundsPause, music);

        RightRewindButton(btnAction, btnState, mousePoint, btnBoundsRightRewind, music);

        LeftRewindButton(btnAction, btnState, mousePoint, btnBoundsLeftRewind, music);

        volumeFlag = LouderButton(btnAction, btnState, mousePoint, btnBoundsLouder, music, volumeFlag);

        volumeFlag = QuietButton(btnAction, btnState, mousePoint, btnBoundsQuiet, music, volumeFlag);

        // Slower - Button
        speedFlag = SlowerButton(btnAction, btnState, mousePoint, btnBoundsSlower, music, speedFlag);

        // Faster - Button
        speedFlag = FasterButton(btnAction, btnState, mousePoint, btnBoundsFaster, music, speedFlag);

        // Bar Rewind - Button
        BarRewindButton(btnAction, btnState, mousePoint, btnBoundsBar1, music);

        UpdateMusicStream(music);
        if (i == 0)
            PauseMusicStream(music);

        timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music) * 400;
        volumeLine = (volumeFlag * 400);
        if (timePlayed > 400) StopMusicStream(music);


        BeginDrawing();

        DrawTextureRec(buttonPlay, sourceRecPlay, (Vector2) { btnBoundsPlay.x, btnBoundsPlay.y }, WHITE); // Draw button 
        DrawTextureRec(buttonPause, sourceRecPause, (Vector2) { btnBoundsPause.x, btnBoundsPause.y }, WHITE);
        DrawTextureRec(buttonRightRewind, sourceRecRightRewind, (Vector2) { btnBoundsRightRewind.x, btnBoundsRightRewind.y }, WHITE);
        DrawTextureRec(buttonLeftRewind, sourceRecLeftRewind, (Vector2) { btnBoundsLeftRewind.x, btnBoundsLeftRewind.y }, WHITE);
        DrawTextureRec(buttonLouder, sourceRecLouder, (Vector2) { btnBoundsLouder.x, btnBoundsLouder.y }, WHITE);
        DrawTextureRec(buttonQuiet, sourceRecQuiet, (Vector2) { btnBoundsQuiet.x, btnBoundsQuiet.y }, WHITE);
        DrawTextureRec(buttonSlower, sourceRecSlower, (Vector2) { btnBoundsSlower.x, btnBoundsSlower.y }, WHITE);
        DrawTextureRec(buttonFaster, sourceRecFaster, (Vector2) { btnBoundsFaster.x, btnBoundsFaster.y }, WHITE);

        ClearBackground(DARKGRAY);// Глобальный бэкграунд

        DrawText("AUDIO PLAYER", 210, 80, 50, BLACK);
        DrawText("Volume", 300, 280, 50, BLACK);

        DrawRectangle(200, 150, 400, 20, GRAY);// Бэкграунд ползунка проигрывателя
        DrawRectangle(200, 150, (int)timePlayed, 20, MAROON);// Ползунок проигрывателя
        DrawRectangleLines(200, 150, 400, 20, BLACK); // Рамка ползунка проигрывателя

        DrawRectangle(200, 350, 400, 20, GRAY);// Бэкграунд ползунка громкости
        DrawRectangle(200, 350, (int)volumeLine, 20, SKYBLUE);// Ползунок громкости
        DrawRectangleLines(200, 350, 400, 20, BLACK); // Рамка ползунка громкости

        DrawRectangle(645, 138, 110, 40, LIGHTGRAY);
        DrawRectangleLines(645, 138, 110, 40, BLACK);
        int time = GetMusicTimePlayed(music);
        int Time = time / 60;
        int time2 = time % 60;
        if (time2 < 10)
            DrawText(TextFormat("0%d:0%d", Time, time2), 650, 140, 40, BLACK);
        else
            DrawText(TextFormat("0%d:%d", Time, time2), 650, 140, 40, BLACK);

        DrawTextureRec(buttonBar1, sourceRecBar1, (Vector2) { btnBoundsBar1.x, btnBoundsBar1.y }, WHITE);
        EndDrawing();
        i = 1;
    }

    UnloadTexture(buttonPlay);
    UnloadTexture(buttonPause);
    UnloadTexture(buttonFaster);
    UnloadTexture(buttonSlower);
    UnloadTexture(buttonLouder);
    UnloadTexture(buttonQuiet);
    UnloadTexture(buttonRightRewind);
    UnloadTexture(buttonLeftRewind);

    UnloadMusicStream(music);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}