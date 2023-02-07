#pragma once

using namespace std;


sf::Event event;

#define MAX_BORDERS 100
#define BORDERS_WIDTH 80
#define BORDERS_SPEED 3
#define PLAYER_SPEED 4

typedef class Player
{
public:
    sf::Vector2f position;
    sf::Vector2f size;
    long long score;
} Player;

typedef class Borders
{
public:
    //sf::RectangleShape rectangle;//Rectangle rec;
    sf::Vector2f position;
    sf::Vector2f size;
} Borders;


const int WEIGHT = 1600;
const int HEIGHT = 800;

sf::RenderWindow window(sf::VideoMode(WEIGHT, HEIGHT), "Simple Flappy Bird");

void InitPlayer(Player* player, sf::RectangleShape* rectanglePlayer)
{
    player->position = { 100, 400 };
    player->size = { 60, 60 };
    player->score = 0;

    rectanglePlayer->setSize(player->size);
    rectanglePlayer->setFillColor((sf::Color::White));
    rectanglePlayer->setPosition(player->position);
}

void TextInit(sf::Font* font, sf::Text* textScore, sf::Text* textNeedToRestart)
{

    textScore->setFont(*font); // font is a sf::Font
    textNeedToRestart->setFont(*font);



    textScore->setCharacterSize(24); // in pixels, not points!
    textNeedToRestart->setCharacterSize(72);

    textScore->setFillColor(sf::Color::Yellow);
    textScore->setOutlineColor(sf::Color::Black);
    textScore->setOutlineThickness(3);

    textNeedToRestart->setFillColor(sf::Color::Yellow);
    textNeedToRestart->setOutlineColor(sf::Color::Black);
    textNeedToRestart->setOutlineThickness(10);
    textNeedToRestart->setPosition(300, 300);
}

void GameRestart(int* j, Player* player, float* rand_numbers, Borders upper_borders[MAX_BORDERS], Borders lower_borders[MAX_BORDERS], int* borders_speed, int* player_speed, bool* stop_game)
{
    *j = 0;
    player->position = { 100, 400 };
    player->score = 0;

    for (int i = 0; i < MAX_BORDERS; i++)
    {
        rand_numbers[i] = rand() % 300;
    }

    for (int i = 0; i < MAX_BORDERS; i++)
    {
        upper_borders[i].size = { 100, 200 + rand_numbers[i] };          upper_borders[i].position = { 500.0f + i * 400, 0 };
        lower_borders[i].size = { 100, 800 - 200 + rand_numbers[i] };    lower_borders[i].position = { 500.0f + i * 400, 200 + rand_numbers[i] + 140 };
    }

    Sleep(200);

    *borders_speed = BORDERS_SPEED;
    *player_speed = PLAYER_SPEED;

    *stop_game = false;
}

void GameMoveLogic(Player* player, sf::RectangleShape* rectanglePlayer, sf::Sprite* Birdsprite, Borders upper_borders[MAX_BORDERS], Borders lower_borders[MAX_BORDERS], int* borders_speed, int* player_speed, sf::RectangleShape rectangleUpBorder[MAX_BORDERS], sf::RectangleShape rectangleDownBorder[MAX_BORDERS], sf::Sound* sound, sf::SoundBuffer* wing)
{
    rectanglePlayer->setSize(player->size);
    rectanglePlayer->setOutlineColor(sf::Color::White);
    rectanglePlayer->setPosition(player->position);
    Birdsprite->setPosition(player->position);
    Birdsprite->setRotation(0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player->position.y -= (*player_speed) * 2;
        Birdsprite->setRotation(-30);
        sound->setBuffer(*wing);
        sound->play();
    }

    player->position.y += *player_speed;

    for (int i = 0; i < MAX_BORDERS; i++)
    {
        upper_borders[i].position.x -= *borders_speed;
        lower_borders[i].position.x -= *borders_speed;

        rectangleUpBorder[i].setSize(upper_borders[i].size);
        rectangleUpBorder[i].setFillColor((sf::Color::Green));
        rectangleUpBorder[i].setPosition(upper_borders[i].position);
        rectangleUpBorder[i].setOutlineColor(sf::Color::Black);
        rectangleUpBorder[i].setOutlineThickness(2);

        rectangleDownBorder[i].setSize(lower_borders[i].size);
        rectangleDownBorder[i].setFillColor((sf::Color::Green));
        rectangleDownBorder[i].setPosition(lower_borders[i].position);
        rectangleDownBorder[i].setOutlineColor(sf::Color::Black);
        rectangleDownBorder[i].setOutlineThickness(2);
    }
}