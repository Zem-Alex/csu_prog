#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <locale.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

void Button_0(Vector2 mousePoint, Rectangle btnBounds0, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds0))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds0, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '0';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '0';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_1(Vector2 mousePoint, Rectangle btnBounds1, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds1))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds1, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '1';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '1';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_2(Vector2 mousePoint, Rectangle btnBounds2, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds2))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds2, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '2';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '2';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_3(Vector2 mousePoint, Rectangle btnBounds3, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds3))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds3, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '3';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '3';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_4(Vector2 mousePoint, Rectangle btnBounds4, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds4))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds4, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '4';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '4';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_5(Vector2 mousePoint, Rectangle btnBounds5, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds5))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds5, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '5';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '5';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_6(Vector2 mousePoint, Rectangle btnBounds6, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds6))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds6, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '6';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '6';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_7(Vector2 mousePoint, Rectangle btnBounds7, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds7))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds7, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '7';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '7';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_8(Vector2 mousePoint, Rectangle btnBounds8, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds8))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds8, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '8';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '8';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_9(Vector2 mousePoint, Rectangle btnBounds9, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber)
{
    if (CheckCollisionPointRec(mousePoint, btnBounds9))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBounds9, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        if (flagNum == false)
        {
            FirsCharNumber[*index] = '9';
            *index = *index + 1;
        }
        else
        {
            if (flagNum == true && flagOperation == true)
            {
                SecondCharNumber[*index] = '9';
                *index = *index + 1;
            }
        }
        btnAction = false;
        btnState = 0;
    }
}

void Button_Plus(Vector2 mousePoint, Rectangle btnBoundsPlus, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsPlus))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsPlus, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = '+';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Minus(Vector2 mousePoint, Rectangle btnBoundsMinus, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsMinus))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsMinus, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = '-';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Mult(Vector2 mousePoint, Rectangle btnBoundsMult, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsMult))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsMult, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = '*';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Div(Vector2 mousePoint, Rectangle btnBoundsDiv, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsDiv))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsDiv, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = '/';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Result(Vector2 mousePoint, Rectangle btnBoundsResult, int btnState, bool btnAction, Sound fxButton, char CharOperation, double* param , double* result, long long FirstIntNum, long long SecondIntNum)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsResult))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsResult, Fade(WHITE, 0.5f));
        EndDrawing();
        Sleep(100);

        switch (CharOperation)
        {
        case '+':
            *result = FirstIntNum + SecondIntNum;
            break;
        case '-':
            *result = FirstIntNum - SecondIntNum;
            break;
        case '*':
            *result = FirstIntNum * SecondIntNum;
            break;
        case '/':
            if (SecondIntNum)
                *result = FirstIntNum / SecondIntNum;
            break;
        case 'c':
            *param = FirstIntNum;
            if (!SecondIntNum)
                *result = cos(*param * PI / 180.0);
            break;
        case 's':
            *param = FirstIntNum;
            if (!SecondIntNum)
                *result = sin(*param * PI / 180.0);
            break;
        case 't':
            *param = FirstIntNum;
            if (!SecondIntNum)
                *result = tan(*param * PI / 180.0);
            break;
        case 'r':
            *param = FirstIntNum;
            if (!SecondIntNum)
                *result = sqrt(*param);
            break;
        case '^':
            *result = pow(FirstIntNum, SecondIntNum);
            break;
        default:
            exit(410);
        }
        //index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Clean(Vector2 mousePoint, Rectangle btnBoundsClean, int btnState, bool btnAction, Sound fxButton, char* CharOperation, double* param, double* result, long long FirstIntNum, long long SecondIntNum, char* FirsCharNumber, char* SecondCharNumber, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsClean))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsClean, Fade(WHITE, 0.5f));
        EndDrawing();
        Sleep(100);

        for (int i = 0; i < 9; i++)
        {
            FirsCharNumber[i] = '\0';
            SecondCharNumber[i] = '\0';
        }

        *CharOperation = '\0';
        *flagNum = false;
        *flagOperation = false;
        *index = 0;
        *saveindex = 0;
        *result = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Back(Vector2 mousePoint, Rectangle btnBoundsBack, int btnState, bool btnAction, Sound fxButton, char* CharOperation, double* param, double* result, long long FirstIntNum, long long SecondIntNum, char* FirsCharNumber, char* SecondCharNumber, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsBack))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsBack, Fade(WHITE, 0.5f));
        EndDrawing();
        Sleep(100);

        if (*flagNum == false && *index)
        {
            FirsCharNumber[*index - 1] = '\0';
            *index = *index - 1;
        }
        else
        {
            if (*index)
            {
                SecondCharNumber[*index - 1] = '\0';
                *index = *index - 1;
            }
            else
            {
                if (*CharOperation != '\0')
                {
                    *flagOperation = false;
                    *CharOperation = '\0';
                }
                else
                {
                    *index = *saveindex;
                    *flagNum = false;
                    FirsCharNumber[*index - 1] = '\0';
                    *index = *index - 1;
                }


            }
        }

        btnAction = false;
        btnState = 0;
    }
}

void Button_Cos(Vector2 mousePoint, Rectangle btnBoundsCos, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsCos))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsCos, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = 'c';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Sin(Vector2 mousePoint, Rectangle btnBoundsSin, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsSin))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsSin, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = 's';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Tan(Vector2 mousePoint, Rectangle btnBoundsTan, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsTan))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsTan, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = 't';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Root(Vector2 mousePoint, Rectangle btnBoundsRoot, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsRoot))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsRoot, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = 'r';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Button_Power(Vector2 mousePoint, Rectangle btnBoundsPower, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index)
{
    if (CheckCollisionPointRec(mousePoint, btnBoundsPower))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySoundMulti(fxButton);

        BeginDrawing();
        DrawRectangleRec(btnBoundsPower, Fade(BLACK, 0.5f));
        EndDrawing();
        Sleep(100);

        *CharOperation = '^';
        *flagNum = true;
        *flagOperation = true;

        if (*saveindex == 0)
            *saveindex = *index;
        *index = 0;

        btnAction = false;
        btnState = 0;
    }
}

void Drawing_Function(Texture2D buttonMainCalc, Texture2D buttonClean, Texture2D buttonBack, Texture2D buttonCos, Texture2D buttonSin, Texture2D buttonTan, Texture2D buttonRoot, Texture2D buttonPower, Texture2D button0, Texture2D button1, Texture2D button2, Texture2D button3, Texture2D button4, Texture2D button5, Texture2D button6, Texture2D button7, Texture2D button8, Texture2D button9, Texture2D buttonPlus, Texture2D buttonMinus, Texture2D buttonMult, Texture2D buttonDiv, Texture2D buttonResult,
    Rectangle sourceRecMainCalc, Rectangle sourceRecClean, Rectangle sourceRecBack, Rectangle sourceRecCos, Rectangle sourceRecSin, Rectangle sourceRecTan, Rectangle sourceRecRoot, Rectangle sourceRecPower, Rectangle sourceRec0, Rectangle sourceRec1, Rectangle sourceRec2, Rectangle sourceRec3, Rectangle sourceRec4, Rectangle sourceRec5, Rectangle sourceRec6, Rectangle sourceRec7, Rectangle sourceRec8, Rectangle sourceRec9, Rectangle sourceRecPlus, Rectangle sourceRecMinus, Rectangle sourceRecMult,
    Rectangle sourceRecDiv, Rectangle sourceRecResult, Rectangle btnBoundsMainCalc, Rectangle btnBoundsClean, Rectangle btnBoundsBack, Rectangle btnBoundsCos, Rectangle btnBoundsSin, Rectangle btnBoundsTan, Rectangle btnBoundsRoot, Rectangle btnBoundsPower, Rectangle btnBounds0, Rectangle btnBounds1, Rectangle btnBounds2, Rectangle btnBounds3, Rectangle btnBounds4, Rectangle btnBounds5, Rectangle btnBounds6, Rectangle btnBounds7, Rectangle btnBounds8, Rectangle btnBounds9, Rectangle btnBoundsPlus,
    Rectangle btnBoundsMinus, Rectangle btnBoundsMult, Rectangle btnBoundsDiv, Rectangle btnBoundsResult, Vector2 mousePoint, char* FirsCharNumber, char* SecondCharNumber, char CharOperation, double result)
{
    ClearBackground(DARKGRAY);// Глобальный бэкграунд

    DrawTextureRec(buttonMainCalc, sourceRecMainCalc, (Vector2) { btnBoundsMainCalc.x, btnBoundsMainCalc.y }, WHITE); // Draw button 
    DrawTextureRec(buttonClean, sourceRecClean, (Vector2) { btnBoundsClean.x, btnBoundsClean.y }, WHITE); // Draw button 
    DrawTextureRec(buttonBack, sourceRecBack, (Vector2) { btnBoundsBack.x, btnBoundsBack.y }, WHITE); // Draw button 
    DrawTextureRec(buttonCos, sourceRecCos, (Vector2) { btnBoundsCos.x, btnBoundsCos.y }, WHITE); // Draw button 
    DrawTextureRec(buttonSin, sourceRecSin, (Vector2) { btnBoundsSin.x, btnBoundsSin.y }, WHITE); // Draw button 
    DrawTextureRec(buttonTan, sourceRecTan, (Vector2) { btnBoundsTan.x, btnBoundsTan.y }, WHITE); // Draw button 
    DrawTextureRec(buttonRoot, sourceRecRoot, (Vector2) { btnBoundsRoot.x, btnBoundsRoot.y }, WHITE); // Draw button 
    DrawTextureRec(buttonPower, sourceRecPower, (Vector2) { btnBoundsPower.x, btnBoundsPower.y }, WHITE); // Draw button 
    DrawTextureRec(button0, sourceRec0, (Vector2) { btnBounds0.x, btnBounds0.y }, WHITE); // Draw button 
    DrawTextureRec(button1, sourceRec1, (Vector2) { btnBounds1.x, btnBounds1.y }, WHITE); // Draw button 
    DrawTextureRec(button2, sourceRec2, (Vector2) { btnBounds2.x, btnBounds2.y }, WHITE); // Draw button 
    DrawTextureRec(button3, sourceRec3, (Vector2) { btnBounds3.x, btnBounds3.y }, WHITE); // Draw button 
    DrawTextureRec(button4, sourceRec4, (Vector2) { btnBounds4.x, btnBounds4.y }, WHITE); // Draw button 
    DrawTextureRec(button5, sourceRec5, (Vector2) { btnBounds5.x, btnBounds5.y }, WHITE); // Draw button 
    DrawTextureRec(button6, sourceRec6, (Vector2) { btnBounds6.x, btnBounds6.y }, WHITE); // Draw button 
    DrawTextureRec(button7, sourceRec7, (Vector2) { btnBounds7.x, btnBounds7.y }, WHITE); // Draw button 
    DrawTextureRec(button8, sourceRec8, (Vector2) { btnBounds8.x, btnBounds8.y }, WHITE); // Draw button 
    DrawTextureRec(button9, sourceRec9, (Vector2) { btnBounds9.x, btnBounds9.y }, WHITE); // Draw button 
    DrawTextureRec(buttonPlus, sourceRecPlus, (Vector2) { btnBoundsPlus.x, btnBoundsPlus.y }, WHITE); // Draw button 
    DrawTextureRec(buttonMinus, sourceRecMinus, (Vector2) { btnBoundsMinus.x, btnBoundsMinus.y }, WHITE); // Draw button 
    DrawTextureRec(buttonMult, sourceRecMult, (Vector2) { btnBoundsMult.x, btnBoundsMult.y }, WHITE); // Draw button 
    DrawTextureRec(buttonDiv, sourceRecDiv, (Vector2) { btnBoundsDiv.x, btnBoundsDiv.y }, WHITE); // Draw button 
    DrawTextureRec(buttonResult, sourceRecResult, (Vector2) { btnBoundsResult.x, btnBoundsResult.y }, WHITE); // Draw button 

    if (CheckCollisionPointRec(mousePoint, btnBounds0))
        DrawRectangleRec(btnBounds0, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds1))
        DrawRectangleRec(btnBounds1, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds2))
        DrawRectangleRec(btnBounds2, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds3))
        DrawRectangleRec(btnBounds3, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds4))
        DrawRectangleRec(btnBounds4, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds5))
        DrawRectangleRec(btnBounds5, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds6))
        DrawRectangleRec(btnBounds6, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds7))
        DrawRectangleRec(btnBounds7, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds8))
        DrawRectangleRec(btnBounds8, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBounds9))
        DrawRectangleRec(btnBounds9, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsPlus))
        DrawRectangleRec(btnBoundsPlus, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsMinus))
        DrawRectangleRec(btnBoundsMinus, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsMult))
        DrawRectangleRec(btnBoundsMult, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsDiv))
        DrawRectangleRec(btnBoundsDiv, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsResult))
        DrawRectangleRec(btnBoundsResult, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsClean))
        DrawRectangleRec(btnBoundsClean, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsBack))
        DrawRectangleRec(btnBoundsBack, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsCos))
        DrawRectangleRec(btnBoundsCos, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsSin))
        DrawRectangleRec(btnBoundsSin, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsTan))
        DrawRectangleRec(btnBoundsTan, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsRoot))
        DrawRectangleRec(btnBoundsRoot, Fade(GRAY, 0.5f));
    if (CheckCollisionPointRec(mousePoint, btnBoundsPower))
        DrawRectangleRec(btnBoundsPower, Fade(GRAY, 0.5f));

    DrawRectangle(95, 35, 198, 47, RAYWHITE);
    DrawRectangleLines(95, 35, 198, 47, GRAY);

    DrawRectangle(95, 95, 198, 47, RAYWHITE);
    DrawRectangleLines(95, 95, 198, 47, GRAY);

    DrawRectangle(55, 70, 31, 31, Fade(GRAY, 0.2f));
    DrawRectangleLines(55, 70, 31, 31, GRAY);

    DrawRectangle(45, 175, 300, 47, Fade(GRAY, 0.2f));
    DrawRectangleLines(45, 175, 300, 47, BLACK);

    DrawText(TextFormat("%s", FirsCharNumber), 100, 40, 40, Fade(BLACK, 0.7f));
    DrawText(TextFormat("%c", CharOperation), 62, 72, 30, BLACK);
    DrawText(TextFormat("%s", SecondCharNumber), 100, 100, 40, Fade(BLACK, 0.7f));
    DrawText(TextFormat("%.1lf", result), 50, 180, 40, BLACK);
}

void UnloadAllTexture(Texture2D buttonMainCalc, Texture2D buttonClean, Texture2D buttonBack, Texture2D buttonCos, Texture2D buttonSin, Texture2D buttonTan, Texture2D buttonRoot, Texture2D buttonPower, Texture2D button0, Texture2D button1, Texture2D button2, Texture2D button3, Texture2D button4, Texture2D button5, Texture2D button6, Texture2D button7, Texture2D button8, Texture2D button9, Texture2D buttonPlus, Texture2D buttonMinus, Texture2D buttonMult, Texture2D buttonDiv, Texture2D buttonResult)
{
    UnloadTexture(buttonMainCalc);
    UnloadTexture(button0);
    UnloadTexture(button1);
    UnloadTexture(button2);
    UnloadTexture(button3);
    UnloadTexture(button4);
    UnloadTexture(button5);
    UnloadTexture(button6);
    UnloadTexture(button7);
    UnloadTexture(button8);
    UnloadTexture(button9);
    UnloadTexture(buttonPlus);
    UnloadTexture(buttonMinus);
    UnloadTexture(buttonMult);
    UnloadTexture(buttonDiv);
    UnloadTexture(buttonResult);
    UnloadTexture(buttonClean);
    UnloadTexture(buttonBack);
    UnloadTexture(buttonCos);
    UnloadTexture(buttonSin);
    UnloadTexture(buttonTan);
    UnloadTexture(buttonRoot);
    UnloadTexture(buttonPower);
}
