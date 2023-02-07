#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <locale.h>

#define MAX_INPUT_CHARS  26

int main(void)
{
	setlocale(LC_ALL, "ru-RU");
	const int screenWidth = 850;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "Hash Utility");

    char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
	int letterCount = 0;
	Rectangle textBox = { 125, 150, 600, 41 };
	bool mouseOnText = false;

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
		else mouseOnText = false;
        if (mouseOnText)
        {
            SetMouseCursor(0);

            int key = GetCharPressed();

            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = GetCharPressed();  // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);


		BeginDrawing();


		ClearBackground(GRAY);

        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawText(name, (int)textBox.x + 5, (int)textBox.y - 1, 40, MAROON);
        DrawRectangleLines(125, 150, 600, 41, BLACK);

		EndDrawing();
	}
	CloseWindow();

	return 0;
}