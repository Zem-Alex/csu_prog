#pragma once

typedef class logo
{
public:
    sf::Vector2f position;
    sf::Vector2f size;
    float xSpeed = 3.0f;
    float ySpeed = 3.0f;
    sf::Texture texture;
    sf::Sprite sprite;
    int r, g, b;
} Logo;

void logoInit(Logo* logo, sf::Sprite* sprite);
void movements(Logo* logo);
void collision(Logo* logo, sf::Sprite* sprite, sf::RenderWindow* window);
void update(Logo* logo, sf::Sprite* sprite, sf::RenderWindow* window);
void closeWindow(sf::RenderWindow* window);