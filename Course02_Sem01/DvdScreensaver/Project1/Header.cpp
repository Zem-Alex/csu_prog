#include <SFML/Graphics.hpp>
#include <time.h>
#include "Header.hpp"

void logoInit(Logo* logo, sf::Sprite* sprite)
{
    logo->r = 255, logo->g = 0, logo->b = 0;
    sprite->setPosition(logo->position);
    sprite->setColor(sf::Color::White);
}

void movements(Logo* logo)
{
	logo->position.x += logo->xSpeed;
	logo->position.y += logo->ySpeed;
}

void collision(Logo* logo, sf::Sprite* sprite, sf::RenderWindow* window)
{
	if (logo->position.x < 0 || logo->position.x > window->getSize().x - sprite->getLocalBounds().width + 5)
        {
            logo->r += 55; logo->b += 55;
            logo->xSpeed = -logo->xSpeed;
        }
        if (logo->position.y < 0 || logo->position.y > window->getSize().y - sprite->getLocalBounds().height + 20)
        {
            logo->ySpeed = -logo->ySpeed;
            logo->g += 55; logo->b -= 55;
        }
}


void update(Logo* logo, sf::Sprite* sprite, sf::RenderWindow* window)
{
    sprite->setPosition(logo->position);
    sprite->setColor(sf::Color(logo->r, logo->g, logo->b));

    window->clear(sf::Color::Black);
    window->draw(*sprite);
    window->display();
}

void closeWindow(sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}


