#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <locale.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

int main(void)
{
    setlocale(LC_ALL, "ru-RU");

    const int screenWidth = 392;
    const int screenHeight = 653;

    InitWindow(screenWidth, screenHeight, "Calculator");

    InitAudioDevice();
    
    Sound fxButton = LoadSound("knopka-vklyucheniya-kassetnogo-pleera.mp3");

    Texture2D buttonMainCalc = LoadTexture("MainCalc.png");
    Texture2D buttonClean = LoadTexture("transparent_button.png");
    Texture2D buttonBack = LoadTexture("transparent_button.png");
    Texture2D buttonCos = LoadTexture("transparent_button.png");
    Texture2D buttonSin = LoadTexture("transparent_button.png");
    Texture2D buttonTan = LoadTexture("transparent_button.png");
    Texture2D buttonRoot = LoadTexture("transparent_button.png");
    Texture2D buttonPower = LoadTexture("transparent_button.png");
    Texture2D button0 = LoadTexture("transparent_button.png");
    Texture2D button1 = LoadTexture("transparent_button.png");
    Texture2D button2 = LoadTexture("transparent_button.png");
    Texture2D button3 = LoadTexture("transparent_button.png");
    Texture2D buttonPlus = LoadTexture("transparent_button.png");
    Texture2D buttonMinus = LoadTexture("transparent_button.png");
    Texture2D buttonMult = LoadTexture("transparent_button.png");
    Texture2D buttonDiv = LoadTexture("transparent_button.png");
    Texture2D buttonResult = LoadTexture("transparent_button.png");
    Texture2D button4 = LoadTexture("transparent_button.png");
    Texture2D button5 = LoadTexture("transparent_button.png");
    Texture2D button6 = LoadTexture("transparent_button.png");
    Texture2D button7 = LoadTexture("transparent_button.png");
    Texture2D button8 = LoadTexture("transparent_button.png");
    Texture2D button9 = LoadTexture("transparent_button.png");

    Rectangle sourceRecMainCalc = { 0, 0, (float)buttonMainCalc.width, (float)buttonMainCalc.height };
    Rectangle sourceRecClean = { 0, 0, (float)buttonClean.width, (float)buttonClean.height };
    Rectangle sourceRecBack = { 0, 0, (float)buttonBack.width, (float)buttonBack.height };
    Rectangle sourceRecCos = { 0, 0, (float)buttonCos.width, (float)buttonCos.height };
    Rectangle sourceRecSin = { 0, 0, (float)buttonSin.width, (float)buttonSin.height };
    Rectangle sourceRecTan = { 0, 0, (float)buttonTan.width, (float)buttonTan.height };
    Rectangle sourceRecRoot = { 0, 0, (float)buttonRoot.width, (float)buttonRoot.height };
    Rectangle sourceRecPower = { 0, 0, (float)buttonPower.width, (float)buttonPower.height };
    Rectangle sourceRec0 = { 0, 0, (float)button0.width, (float)button0.height };
    Rectangle sourceRec1 = { 0, 0, (float)button1.width, (float)button1.height };
    Rectangle sourceRec2 = { 0, 0, (float)button2.width, (float)button2.height };
    Rectangle sourceRec3 = { 0, 0, (float)button3.width, (float)button3.height };
    Rectangle sourceRecPlus = { 0, 0, (float)buttonPlus.width, (float)buttonPlus.height };
    Rectangle sourceRecMinus = { 0, 0, (float)buttonMinus.width, (float)buttonMinus.height };
    Rectangle sourceRecMult = { 0, 0, (float)buttonMult.width, (float)buttonMult.height };
    Rectangle sourceRecDiv = { 0, 0, (float)buttonDiv.width, (float)buttonDiv.height };
    Rectangle sourceRecResult = { 0, 0, (float)buttonResult.width, (float)buttonResult.height };
    Rectangle sourceRec4 = { 0, 0, (float)button4.width, (float)button4.height };
    Rectangle sourceRec5 = { 0, 0, (float)button5.width, (float)button5.height };
    Rectangle sourceRec6 = { 0, 0, (float)button6.width, (float)button6.height };
    Rectangle sourceRec7 = { 0, 0, (float)button7.width, (float)button7.height };
    Rectangle sourceRec8 = { 0, 0, (float)button8.width, (float)button8.height };
    Rectangle sourceRec9 = { 0, 0, (float)button9.width, (float)button9.height };

    Rectangle btnBoundsMainCalc = { 0, 0, (float)buttonMainCalc.width, (float)buttonMainCalc.height }; // расположение кнопки
    Rectangle btnBoundsClean = { 199, 262, (float)buttonClean.width, (float)buttonClean.height };
    Rectangle btnBoundsBack = { 297.5, 262, (float)buttonBack.width, (float)buttonBack.height };
    Rectangle btnBoundsCos = { 100.5, 262, (float)buttonCos.width, (float)buttonCos.height };
    Rectangle btnBoundsSin = { 2, 262, (float)buttonSin.width, (float)buttonSin.height };
    Rectangle btnBoundsTan = { 2, 328, (float)buttonTan.width, (float)buttonTan.height };
    Rectangle btnBoundsRoot = { 199, 328, (float)buttonRoot.width, (float)buttonRoot.height };
    Rectangle btnBoundsPower = { 100.5, 328, (float)buttonPower.width, (float)buttonPower.height };
    Rectangle btnBounds0 = { 100.5, 591.5, (float)button0.width, (float)button0.height };
    Rectangle btnBounds1 = { 2, 526, (float)button1.width, (float)button1.height };
    Rectangle btnBounds2 = { 100.5, 526, (float)button2.width, (float)button2.height }; //+98.5
    Rectangle btnBounds3 = { 199, 526, (float)button3.width, (float)button3.height };
    Rectangle btnBoundsPlus = { 297.5, 526, (float)buttonPlus.width, (float)buttonPlus.height };
    Rectangle btnBoundsMinus = { 297.5, 460.5, (float)buttonMinus.width, (float)buttonMinus.height };
    Rectangle btnBoundsMult = { 297.5, 395, (float)buttonMult.width, (float)buttonMult.height };
    Rectangle btnBoundsDiv = { 297.5, 328, (float)buttonDiv.width, (float)buttonDiv.height };
    Rectangle btnBoundsResult = { 297.5, 591.5, (float)buttonResult.width, (float)buttonResult.height };
    Rectangle btnBounds4 = { 2, 460.5, (float)button4.width, (float)button4.height };//-65.5
    Rectangle btnBounds5 = { 100.5, 460.5, (float)button5.width, (float)button5.height };
    Rectangle btnBounds6 = { 199, 460.5, (float)button6.width, (float)button6.height };
    Rectangle btnBounds7 = { 2, 394, (float)button7.width, (float)button7.height };
    Rectangle btnBounds8 = { 100.5, 394, (float)button8.width, (float)button8.height };
    Rectangle btnBounds9 = { 199, 394, (float)button9.width, (float)button9.height };

    int btnState = 0;              // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;

    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);

    short index = 0, saveindex = 0;
    char FirsCharNumber[9] = {'\0'}, SecondCharNumber[9] = { '\0' }, CharOperation = '\0';
    long long FirstIntNum = 0, SecondIntNum = 0; double param = 0, result = 0;
    bool flagNum = false, flagOperation = false;

    while (!WindowShouldClose())
    {
        if (flagNum == false)
            FirstIntNum = atoll(FirsCharNumber);
        else
        {
            if (flagNum == true)
                SecondIntNum = atoll(SecondCharNumber);
        }

        if (index >= 8)
        {
            if (flagNum == false)
            {
                flagNum = true;
                saveindex = index;
                index = 0;
            }
            else
                break;
        }

        mousePoint = GetMousePosition();
        btnAction = false;

        ///  Buttons for some functions

        // Button '0'
        Button_0(mousePoint, btnBounds0, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '1'
        Button_1(mousePoint, btnBounds1, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '2'
        Button_2(mousePoint, btnBounds2, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '3'
        Button_3(mousePoint, btnBounds3, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '4'
        Button_4(mousePoint, btnBounds4, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '5'
        Button_5(mousePoint, btnBounds5, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '6'
        Button_6(mousePoint, btnBounds6, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '7'
        Button_7(mousePoint, btnBounds7, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '8'
        Button_8(mousePoint, btnBounds8, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button '9'
        Button_9(mousePoint, btnBounds9, btnState, btnAction, fxButton, flagNum, FirsCharNumber, &index, flagOperation, SecondCharNumber);

        // Button 'Plus'
        Button_Plus(mousePoint, btnBoundsPlus, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Minus'
        Button_Minus(mousePoint, btnBoundsMinus, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Mult'
        Button_Mult(mousePoint, btnBoundsMult, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Div'
        Button_Div(mousePoint, btnBoundsDiv, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Result'
        Button_Result(mousePoint, btnBoundsResult, btnState, btnAction, fxButton, CharOperation, &param, &result, FirstIntNum, SecondIntNum);
        
        // Button 'Clean'
        Button_Clean(mousePoint, btnBoundsClean, btnState, btnAction, fxButton, &CharOperation, &param, &result, FirstIntNum, SecondIntNum, FirsCharNumber, SecondCharNumber, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Back'

        Button_Back(mousePoint, btnBoundsBack, btnState, btnAction, fxButton, &CharOperation, &param, &result, FirstIntNum, SecondIntNum, FirsCharNumber, SecondCharNumber, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Cos'
        Button_Cos(mousePoint, btnBoundsCos, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Sin'
        Button_Sin(mousePoint, btnBoundsSin, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Tan'
        Button_Tan(mousePoint, btnBoundsTan, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Root'
        Button_Root(mousePoint, btnBoundsRoot, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        // Button 'Power'
        Button_Power(mousePoint, btnBoundsPower, btnState, btnAction, fxButton, &CharOperation, &flagNum, &flagOperation, &saveindex, &index);

        BeginDrawing();

        Drawing_Function(buttonMainCalc, buttonClean, buttonBack, buttonCos, buttonSin, buttonTan, buttonRoot, buttonPower, button0, button1, button2, button3, button4, button5, button6, button7, button8, button9, buttonPlus, buttonMinus, buttonMult, buttonDiv, buttonResult,
            sourceRecMainCalc, sourceRecClean, sourceRecBack, sourceRecCos, sourceRecSin, sourceRecTan, sourceRecRoot, sourceRecPower, sourceRec0, sourceRec1, sourceRec2, sourceRec3, sourceRec4, sourceRec5, sourceRec6, sourceRec7, sourceRec8, sourceRec9, sourceRecPlus, sourceRecMinus, sourceRecMult,
            sourceRecDiv, sourceRecResult, btnBoundsMainCalc, btnBoundsClean, btnBoundsBack, btnBoundsCos, btnBoundsSin, btnBoundsTan, btnBoundsRoot, btnBoundsPower, btnBounds0, btnBounds1, btnBounds2, btnBounds3, btnBounds4, btnBounds5, btnBounds6, btnBounds7, btnBounds8, btnBounds9, btnBoundsPlus,
            btnBoundsMinus, btnBoundsMult, btnBoundsDiv, btnBoundsResult, mousePoint, FirsCharNumber, SecondCharNumber, CharOperation, result);

        EndDrawing();
    }

    UnloadAllTexture(buttonMainCalc, buttonClean, buttonBack, buttonCos, buttonSin, buttonTan, buttonRoot, buttonPower, button0, button1, button2, button3, button4, button5, button6, button7, button8, button9, buttonPlus, buttonMinus, buttonMult, buttonDiv, buttonResult);

    UnloadSound(fxButton);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}