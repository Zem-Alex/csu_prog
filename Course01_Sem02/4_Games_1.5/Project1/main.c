#include "raylib.h"

#define PLAYER_MAX_SCORE 3

typedef struct Player 
{
    Vector2 position;
    Vector2 size;
    int score;
} Player;

int main(void)
{
    const int screenWidth = 1300;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "BenPong");
    InitAudioDevice();

    Sound fxButtonYes = LoadSound("Yes.mp3");
    Sound fxButtonNo = LoadSound("No.mp3");
    Sound fxButtonPause = LoadSound("Pause.mp3");
    Sound fxButtonHohoho = LoadSound("hohoho.mp3");

    Vector2 ballPosition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Vector2 ballSpeed = { 6.0f, 4.0f };

    Player player1 = { 0 }, player2 = { 0 };

    player1.position = (Vector2){ 0 , screenHeight / 2 - 70 };
    player1.size = (Vector2){ 10, 120 };
    player1.score = 0;

    player2.position = (Vector2){ player1.position.x + 1290, player1.position.y };
    player2.size = player1.size;
    player2.score = player1.score;

    int ballRadius = 15;

    bool pause = true;

    SetTargetFPS(60); 

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            PlaySoundMulti(fxButtonPause);
            pause = !pause;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            PlaySoundMulti(fxButtonPause);
            //pause = !pause;
            player1.position = (Vector2){ 0 , screenHeight / 2 - 70 };
            player2.position = (Vector2){ player1.position.x + 1290, player1.position.y };
            player1.score = 0;
            player2.score = 0;
            ballPosition.x = GetScreenWidth() / 2.0f;
            ballPosition.y = GetScreenHeight() / 2.0f;
            ballSpeed.x = 6.0f;
            ballSpeed.y = 4.0f;

        }

        if (!pause)
        {
            if (IsKeyDown(KEY_W))
                if (player1.position.y - 15 >= 0)
                    player1.position.y -= 8;

            if (IsKeyDown(KEY_S))
                if (player1.position.y + 131 <= GetScreenHeight())
                    player1.position.y += 8;

            if (IsKeyDown(KEY_UP))
                if (player2.position.y - 15 >= 0)
                    player2.position.y -= 8;

            if (IsKeyDown(KEY_DOWN))
                if (player2.position.y + 131 <= GetScreenHeight())
                    player2.position.y += 8;

            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            // Ñheck the collision tile of first (left) player and the ball
            if ((ballPosition.x <= ballRadius + 16) && (ballPosition.y <= player1.position.y + player1.size.y + 26) && (ballPosition.y >= player1.position.y - 26))
            {
                PlaySoundMulti(fxButtonYes);
                ballSpeed.x s= -1.1f;
            }

            else // Ñheck the collision tile of second (right) player and the ball
                if ((ballPosition.x >= (GetScreenWidth() - ballRadius - 16)) && (ballPosition.y <= player2.position.y + player2.size.y + 26) && (ballPosition.y >= player2.position.y - 26))
                {
                    PlaySoundMulti(fxButtonYes);
                    ballSpeed.x *= -1.1f;
                }


            if (ballPosition.x < ballRadius)
            {
                player2.score++;
                ballPosition.x = GetScreenWidth() / 2.0f;
                ballPosition.y = GetScreenHeight() / 2.0f;
                ballSpeed.x = 6.0f;
                ballSpeed.y = 4.0f;
                player1.position = (Vector2){ 0 , screenHeight / 2 - 70 };
                player2.position = (Vector2){ player1.position.x + 1290, player1.position.y };

                pause = !pause;
                if (player1.score >= PLAYER_MAX_SCORE || player2.score >= PLAYER_MAX_SCORE)
                {
                    PlaySoundMulti(fxButtonHohoho);
                }
                else
                    PlaySoundMulti(fxButtonNo);
            }

            if (ballPosition.x > (GetScreenWidth() - ballRadius))
            {
                player1.score++;
                ballPosition.x = GetScreenWidth() / 2.0f;
                ballPosition.y = GetScreenHeight() / 2.0f;
                ballSpeed.x = 6.0f;
                ballSpeed.y = 4.0f;
                player1.position = (Vector2){ 0 , screenHeight / 2 - 70 };
                player2.position = (Vector2){ player1.position.x + 1290, player1.position.y };
                
                pause = !pause;
                if (player1.score >= PLAYER_MAX_SCORE || player2.score >= PLAYER_MAX_SCORE)
                {
                    PlaySoundMulti(fxButtonHohoho);
                }
                else
                    PlaySoundMulti(fxButtonNo);
            }

            //Check the collision of Upper and Lower walls with the ball
            if ((ballPosition.y >= (GetScreenHeight() - ballRadius - 16)) || (ballPosition.y <= ballRadius + 16))
                ballSpeed.y *= -1.f;

            

        }

        BeginDrawing();

        ClearBackground(RED); 

        DrawRectangle(0, 8, 1300, 634, BLACK); // Border of wall
        DrawRectangle(0, 10, 1300, 630, LIGHTGRAY); // Main game field
        
        DrawText(TextFormat("%d \t\t\t\t\t %d", player1.score, player2.score), 500, 100, 60, GRAY); // Game score

        DrawCircleV(ballPosition, (float)ballRadius + 3.f, BLACK); // Border of Ball
        DrawCircleV(ballPosition, (float)ballRadius, GOLD); // Ball

        DrawRectangle(player1.position.x, player1.position.y, player1.size.x, player1.size.y, BLACK); // Border of platforme of first player
        DrawRectangle(player1.position.x, player1.position.y + 3, player1.size.x - 3, player1.size.y - 6, PINK); // Platforme of first player

        DrawRectangle(player2.position.x, player2.position.y, player2.size.x, player2.size.y, BLACK); // Border of platforme of second player
        DrawRectangle(player2.position.x + 3, player2.position.y + 3, player2.size.x + 3, player2.size.y - 6, SKYBLUE); // Platforme of second player

        if (pause) 
            if (player1.score < PLAYER_MAX_SCORE && player2.score < PLAYER_MAX_SCORE)
                DrawText("PRESS SPACE TO PLAY", 300, 200, 60, DARKGRAY);
            else if (player1.score >= PLAYER_MAX_SCORE)
            {
                DrawText("\t\t\t\t\tPLAYER 1 WON!\n\nPRESS ENTER TO RESTART", 250, 200, 60, DARKGRAY); 
            }
            else
            {
                DrawText("\t\t\t\t\tPLAYER 2 WON!\n\nPRESS ENTER TO RESTART", 250, 200, 60, DARKGRAY);
            }

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    UnloadSound(fxButtonYes);
    UnloadSound(fxButtonNo);
    UnloadSound(fxButtonPause);
    UnloadSound(fxButtonHohoho);

    return 0;
}