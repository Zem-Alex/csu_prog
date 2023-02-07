#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include <locale.h>
#include <string.h>

void AudioList();

void PlayButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsPlay, Music music);
void PauseButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsPause, Music music);

void RightRewindButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsRightRewind, Music music);
void LeftRewindButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsLeftRewind, Music music);
void BarRewindButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsBar1, Music music);

float LouderButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsLouder, Music music, float volumeFlag);
float QuietButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsQuiet, Music music, float volumeFlag);

float SlowerButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsSlower, Music music, float speedFlag);
float FasterButton(bool btnAction, int btnState, Vector2 mousePoint, Rectangle btnBoundsFaster, Music music, float speedFlag);

