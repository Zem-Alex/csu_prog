#pragma once

#include <iostream>
#include <time.h>
#include <map>
#include <random>
#include <SFML/Graphics.hpp>
#include <cassert>

using namespace std;

const int WEIGHT = 1400;
const int HEIGHT = 700;
const int LENGTH = 1000000;


void topKFrequent(int* nums, int* map);

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG& generator);

unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue);
