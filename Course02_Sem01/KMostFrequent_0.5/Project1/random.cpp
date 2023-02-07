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
    // ������ ������-���������� ��� ��������� ���������� �����.
    std::random_device device;
    // �������� ��������� ����� ������������������
    generator.engine.seed(device());
}

// ���������� ����� ����� � ��������� [minValue, maxValue)
unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue)
{
    // ��������� ������������ ����������
    assert(minValue < maxValue);

    // ������ �������������
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    // ��������� ��������������� �����: ������� ������������� ��� �������,
    //  ������� ��������� ������������ ����� ����� ��� ��������.
    return distribution(generator.engine);
}
