#include <iostream>
#include <time.h>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include <sstream>
#include <Windows.h>
#include "game.hpp"

int main(void)
{
    srand(time(NULL));

    Player player;
    sf::RectangleShape rectanglePlayer;
    
    InitPlayer(&player, &rectanglePlayer);

    system("dir");

    sf::SoundBuffer wing, hit, point;
    wing.loadFromFile("wing.wav");
    hit.loadFromFile("hit.wav");
    point.loadFromFile("point.wav");
    sf::Sound sound, sound2;
    sound.setVolume(50.f);
    sound.setLoop(false);

    sound2.setVolume(50.f);
    sound2.setLoop(false);
    
    sf::Texture BirdText0, BirdText1, BirdText2;//создаем объект Texture (текстура)
    BirdText0.loadFromFile("bird0.png");//загружаем картинку
    BirdText1.loadFromFile("bird1.png");
    BirdText2.loadFromFile("bird2.png");

    sf::Sprite Birdsprite;//создаем объект Sprite(спрайт)
    Birdsprite.setTexture(BirdText0);//передаЄм в него объект Texture (текстуры)
    Birdsprite.setPosition(50, 25);//задаем начальные координаты по€влени€ спрайта

    sf::RectangleShape rectangleUpBorder[MAX_BORDERS];
    sf::RectangleShape rectangleDownBorder[MAX_BORDERS];

    Borders upper_borders[MAX_BORDERS];
    Borders lower_borders[MAX_BORDERS];

    float rand_numbers[MAX_BORDERS] = { 0 };
    int borders_speed = BORDERS_SPEED, player_speed = PLAYER_SPEED, j = 0;
    bool stop_game = false; long long index = 0;

    for (int i = 0; i < MAX_BORDERS; i++)
    {
        rand_numbers[i] = rand() % 450;
    }

    for (int i = 0; i < MAX_BORDERS; i++)
    {
        upper_borders[i].size = { 100, 200 + rand_numbers[i] };          upper_borders[i].position = { 500.0f + i * 400, 0 };
        lower_borders[i].size = { 100, 800 - 200 + rand_numbers[i] };    lower_borders[i].position = { 500.0f + i * 400, 200 + rand_numbers[i] + 140 };
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return-1;// error...

    sf::Text textScore, textNeedToRestart;
    std::ostringstream playerScoreString;    // объ€вили переменную

    TextInit(&font, &textScore, &textNeedToRestart);

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        window.setFramerateLimit(60 + player.score * 2);

        GameMoveLogic(&player, &rectanglePlayer, &Birdsprite, upper_borders, lower_borders, &borders_speed, &player_speed, rectangleUpBorder, rectangleDownBorder, &sound, &wing);

        if (player.position.x >= upper_borders[j].position.x + 101)
        {
            ++j;
            player.score++;
            sound2.setBuffer(point);
            sound2.play();
        }
        if (((player.position.x + player.size.y >= upper_borders[j].position.x - 10 && player.position.y <= 200 + rand_numbers[j] && player.position.x <= upper_borders[j].position.x + 100 - 10) || (player.position.x + player.size.y >= upper_borders[j].position.x - 10 && player.position.y >= 200 + rand_numbers[j] + 8 + 80 && player.position.x <= upper_borders[j].position.x + 100 - 10)) && (stop_game != true))
        {
            borders_speed = 0;
            player_speed = 0;
            stop_game = true;
            sound2.setBuffer(hit);
            sound2.play();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            GameRestart(&j, &player, rand_numbers, upper_borders, lower_borders, &borders_speed, &player_speed, &stop_game);
        }

        //..................................................................DRAWING........................................................................

        window.clear(sf::Color::White);

        window.draw(rectanglePlayer);
 

        for (int i = 0; i < MAX_BORDERS; i++)
        {
            window.draw(rectangleUpBorder[i]);
            window.draw(rectangleDownBorder[i]);
            
        }
        
        
        if (index > 60)
        {
            if (index < 80)
            {
                Birdsprite.setTexture(BirdText0);
                window.draw(Birdsprite);
                index++;
            }
            else
            {
                Birdsprite.setTexture(BirdText0);
                window.draw(Birdsprite);
                index = 0;
                
            }
        }
        else if (index > 40)
        {
            Birdsprite.setTexture(BirdText1);
            window.draw(Birdsprite);
            index++;
        }
        else if (index > 20)
        {
            Birdsprite.setTexture(BirdText2);
            window.draw(Birdsprite);
            index++;
        }
        else
        {
            Birdsprite.setTexture(BirdText1);
            window.draw(Birdsprite);
            index++;
        }

        playerScoreString.str("");
        playerScoreString.clear();
        playerScoreString << player.score;
        textScore.setString("score:" + playerScoreString.str());
        window.draw(textScore);

        textNeedToRestart.setString("PRESS ENTER TO RESTART");
        if (stop_game == true)
            window.draw(textNeedToRestart);
        
        window.display();
    }

    window.close();

    return 0;
}