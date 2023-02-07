#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <locale.h>
#include <string.h>

#define ERR_OPEN_FILE "ERROR: couldn't open a file\n"

void AudioList()
{
    printf_s("Choose name audio:\n");
    system("dir /b /s /a-d * > file_names.txt");
    FILE* input; char c = 0; int count = 0;
    if (fopen_s(&input, "file_names.txt", "r"))
    {
        printf_s(ERR_OPEN_FILE);
        _fcloseall();
        exit(1);
    }
    while (fscanf_s(input, "%c ", &c, 1) != EOF)
    {
        count++;
    }
    rewind(input);
    char* str = 0; str = (char*)malloc(count * sizeof(char));
    for (int i = 0; i < count; ++i)
    {
        fscanf_s(input, "%c", &str[i], 1);
    }
    rewind(input);
    for (int i = 0; i < count; ++i)
    {
        if (str[i] == 'r' && str[i + 9] == 'M')
        {

            while (str[i] != '\n')
            {
                printf_s("%c", str[i]);
                i++;
            }
            printf_s("\n");
        }
    }
    _fcloseall();
}

void PlayButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsPlay, Music music) 
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsPlay))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        ResumeMusicStream(music);
        btnAction = false;
        btnState = 0;
    }
}

void PauseButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsPause, Music music) 
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsPause))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PauseMusicStream(music);
        btnAction = false;
        btnState = 0;
    }
}

void RightRewindButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsRightRewind, Music music) 
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsRightRewind))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        if (GetMusicTimePlayed(music) < GetMusicTimeLength(music) - 5)
            SeekMusicStream(music, GetMusicTimePlayed(music) + 5);
        btnAction = false;
        btnState = 0;
    }
}

void LeftRewindButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsLeftRewind, Music music) 
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsLeftRewind))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        if (GetMusicTimePlayed(music) > 5)
            SeekMusicStream(music, GetMusicTimePlayed(music) - 5);
        btnAction = false;
        btnState = 0;
    }
}

void BarRewindButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsBar1, Music music)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsBar1))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        int TimeScrool = GetMouseX() - 200;
        printf_s("<%d>", TimeScrool);

        if (GetMusicTimeLength(music) * TimeScrool / 400 > 5 && GetMusicTimeLength(music) * TimeScrool / 400 < (GetMusicTimeLength(music) - 5))
        {
            SeekMusicStream(music, GetMusicTimeLength(music) * TimeScrool / 400);
        }

        btnAction = false;
        btnState = 0;
    }
}

float LouderButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsLouder, Music music, float volumeFlag) 
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsLouder))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction && volumeFlag < 1)
    {
        volumeFlag += 0.1;
        printf_s("(%f)", volumeFlag);
        SetMusicVolume(music, volumeFlag);
        btnAction = false;
        btnState = 0;
    }
    else
    {
        btnAction = false;
        btnState = 0;
    }
    return volumeFlag;
}

float QuietButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsQuiet, Music music, float volumeFlag)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsQuiet))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction && volumeFlag > 0.1)
    {
        volumeFlag -= 0.1;
        printf_s("(%f)", volumeFlag);
        SetMusicVolume(music, volumeFlag);
        btnAction = false;
        btnState = 0;
    }
    else
    {
        btnAction = false;
        btnState = 0;
    }
    return volumeFlag;
}

float SlowerButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsSlower, Music music, float speedFlag)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsSlower))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        speedFlag -= 0.25;
        SetMusicPitch(music, speedFlag);
        btnAction = false;
        btnState = 0;
    }
    return speedFlag;
}

float FasterButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsFaster, Music music, float speedFlag)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsFaster))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        speedFlag += 0.25;
        SetMusicPitch(music, speedFlag);
        btnAction = false;
        btnState = 0;
    }
    return speedFlag;
}