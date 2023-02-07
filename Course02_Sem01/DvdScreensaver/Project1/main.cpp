#include <SFML/Graphics.hpp>
#include "Header.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "DVD ScreenSaver", sf::Style::Titlebar | sf::Style::Close);

    Logo logo;
    
    if (!logo.texture.loadFromFile("DVD_logo.svg1.png"))
        return EXIT_FAILURE;

    sf::Sprite sprite(logo.texture);

    window.setFramerateLimit(200);
    
    logoInit(&logo, &sprite);

    while (window.isOpen())
    {
        closeWindow(&window); // check close or not the window

        movements(&logo);  // movement of logo

        collision(&logo, &sprite, &window); //collision with walls and colors change

        update(&logo, &sprite, &window); //update and draw 
    }
    return 0;
}