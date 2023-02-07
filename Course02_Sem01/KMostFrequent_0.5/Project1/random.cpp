#pragma once

#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <cassert>
#include "random.hpp"
#include <map>
#include <random>

void topKFrequent(int* nums, int* map)
{
    map[10] = { 0 };

    for (int i = 0; i < LENGTH; i++)
    {
        map[nums[i]]++;
    }

    for (int i = 0; i < 10; i++)
    {
        if (map[i])
            cout << "'" << i << "': " << map[i] << endl;
    }
    cout << endl;
}

void initGenerator(PRNG& generator)
{
    // Создаём псевдо-устройство для получения случайного зерна.
    std::random_device device;
    // Получаем случайное зерно последовательности
    generator.engine.seed(device());
}

// Генерирует целое число в диапазоне [minValue, maxValue)
unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}
