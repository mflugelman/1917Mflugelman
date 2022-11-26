// ProyectoFinalCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Unit.h"

using namespace std;

int main()
{
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    vector<Unit*> spawnedShape;


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "1917");
    window.setFramerateLimit(60);
    
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

            if (event.type == sf::Event::MouseButtonPressed)
            {
                cout << "mose pressed" << endl;
                sf::Vector2i position = sf::Mouse::getPosition(window);
                cout << position.x << position.y;

                Unit* unit= new Unit(6 , 10.0f);
                unit->setPosition(position.x, position.y);

                spawnedShape.push_back(unit);
            }
        }

        window.clear();

        for (int i = 0; i < spawnedShape.size(); i++)
        {
            spawnedShape[i]->move_y(1);
        
            window.draw(*spawnedShape[i]);
        }

        window.draw(home_base);
        window.draw(enemy_base);

        window.display();
    }


    for (int i = 0; i < spawnedShape.size(); i++)
        delete spawnedShape[i];

    return 0;
}


