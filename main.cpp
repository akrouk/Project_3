#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"

int main()
{
    //Creates window and menu object for the board
    sf::RenderWindow window(sf::VideoMode(1920,1080), "SFML works!");
    Menu menu;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Checks for a mouse press, and records location before going to checkClick
            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto pos = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left)
                    menu.checkClick(sf::Vector2f(pos.x, pos.y));
            }
        }
        //Clears window, draws, then displays each frame
        window.clear();
        menu.Draw(window);
        window.display();
    }

    return 0;
}