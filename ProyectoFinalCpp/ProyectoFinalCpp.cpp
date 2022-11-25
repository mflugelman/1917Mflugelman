// ProyectoFinalCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>


int main()
{
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "1917");

    sf::Vector2f trench(WINDOW_WIDTH, 50);

    sf::RectangleShape home_base(trench);
    home_base.setFillColor(sf::Color::Green);
    home_base.setPosition(0, WINDOW_HEIGHT - 50);

    sf::RectangleShape enemy_base(trench);
    enemy_base.setFillColor(sf::Color::Red);
    enemy_base.setPosition(0, 0);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(home_base);
        window.draw(enemy_base);
        window.display();
    }

    return 0;
}