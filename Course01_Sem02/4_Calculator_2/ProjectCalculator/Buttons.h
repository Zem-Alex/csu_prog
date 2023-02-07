#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <locale.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265

void Button_0(Vector2 mousePoint, Rectangle btnBounds0, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_1(Vector2 mousePoint, Rectangle btnBounds1, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_2(Vector2 mousePoint, Rectangle btnBounds2, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_3(Vector2 mousePoint, Rectangle btnBounds3, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_4(Vector2 mousePoint, Rectangle btnBounds4, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_5(Vector2 mousePoint, Rectangle btnBounds5, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_6(Vector2 mousePoint, Rectangle btnBounds6, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_7(Vector2 mousePoint, Rectangle btnBounds7, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_8(Vector2 mousePoint, Rectangle btnBounds8, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);
void Button_9(Vector2 mousePoint, Rectangle btnBounds9, int btnState, bool btnAction, Sound fxButton, bool flagNum, char* FirsCharNumber, short* index, bool flagOperation, char* SecondCharNumber);

void Button_Plus(Vector2 mousePoint, Rectangle btnBoundsPlus, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Minus(Vector2 mousePoint, Rectangle btnBoundsMinus, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Mult(Vector2 mousePoint, Rectangle btnBoundsMult, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Div(Vector2 mousePoint, Rectangle btnBoundsDiv, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);

void Button_Result(Vector2 mousePoint, Rectangle btnBoundsResult, int btnState, bool btnAction, Sound fxButton, char CharOperation, double* param, double* result, long long FirstIntNum, long long SecondIntNum);
void Button_Clean(Vector2 mousePoint, Rectangle btnBoundsClean, int btnState, bool btnAction, Sound fxButton, char* CharOperation, double* param, double* result, long long FirstIntNum, long long SecondIntNum, char* FirsCharNumber, char* SecondCharNumber, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Back(Vector2 mousePoint, Rectangle btnBoundsBack, int btnState, bool btnAction, Sound fxButton, char* CharOperation, double* param, double* result, long long FirstIntNum, long long SecondIntNum, char* FirsCharNumber, char* SecondCharNumber, bool* flagNum, bool* flagOperation, short* saveindex, short* index);

void Button_Cos(Vector2 mousePoint, Rectangle btnBoundsCos, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Sin(Vector2 mousePoint, Rectangle btnBoundsSin, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Tan(Vector2 mousePoint, Rectangle btnBoundsTan, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Root(Vector2 mousePoint, Rectangle btnBoundsRoot, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);
void Button_Power(Vector2 mousePoint, Rectangle btnBoundsPower, int btnState, bool btnAction, Sound fxButton, char* CharOperation, bool* flagNum, bool* flagOperation, short* saveindex, short* index);

void Drawing_Function(Texture2D buttonMainCalc, Texture2D buttonClean, Texture2D buttonBack, Texture2D buttonCos, Texture2D buttonSin, Texture2D buttonTan, Texture2D buttonRoot, Texture2D buttonPower, Texture2D button0, Texture2D button1, Texture2D button2, Texture2D button3, Texture2D button4, Texture2D button5, Texture2D button6, Texture2D button7, Texture2D button8, Texture2D button9, Texture2D buttonPlus, Texture2D buttonMinus, Texture2D buttonMult, Texture2D buttonDiv, Texture2D buttonResult,
    Rectangle sourceRecMainCalc, Rectangle sourceRecClean, Rectangle sourceRecBack, Rectangle sourceRecCos, Rectangle sourceRecSin, Rectangle sourceRecTan, Rectangle sourceRecRoot, Rectangle sourceRecPower, Rectangle sourceRec0, Rectangle sourceRec1, Rectangle sourceRec2, Rectangle sourceRec3, Rectangle sourceRec4, Rectangle sourceRec5, Rectangle sourceRec6, Rectangle sourceRec7, Rectangle sourceRec8, Rectangle sourceRec9, Rectangle sourceRecPlus, Rectangle sourceRecMinus, Rectangle sourceRecMult,
    Rectangle sourceRecDiv, Rectangle sourceRecResult, Rectangle btnBoundsMainCalc, Rectangle btnBoundsClean, Rectangle btnBoundsBack, Rectangle btnBoundsCos, Rectangle btnBoundsSin, Rectangle btnBoundsTan, Rectangle btnBoundsRoot, Rectangle btnBoundsPower, Rectangle btnBounds0, Rectangle btnBounds1, Rectangle btnBounds2, Rectangle btnBounds3, Rectangle btnBounds4, Rectangle btnBounds5, Rectangle btnBounds6, Rectangle btnBounds7, Rectangle btnBounds8, Rectangle btnBounds9, Rectangle btnBoundsPlus,
    Rectangle btnBoundsMinus, Rectangle btnBoundsMult, Rectangle btnBoundsDiv, Rectangle btnBoundsResult, Vector2 mousePoint, char* FirsCharNumber, char* SecondCharNumber, char CharOperation, double result);
void UnloadAllTexture(Texture2D buttonMainCalc, Texture2D buttonClean, Texture2D buttonBack, Texture2D buttonCos, Texture2D buttonSin, Texture2D buttonTan, Texture2D buttonRoot, Texture2D buttonPower, Texture2D button0, Texture2D button1, Texture2D button2, Texture2D button3, Texture2D button4, Texture2D button5, Texture2D button6, Texture2D button7, Texture2D button8, Texture2D button9, Texture2D buttonPlus, Texture2D buttonMinus, Texture2D buttonMult, Texture2D buttonDiv, Texture2D buttonResult);