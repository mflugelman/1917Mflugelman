// ProyectoFinalCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "Button.h"
#include "ButtonGroup.h"

using namespace std;


int main()
{
    srand(time(NULL));

    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    UnitType selectedUnit = INFANTRY;

    //vector<Unit*> spawnedShape;
    vector<shared_ptr<Unit>> spawnedShape;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "1917");
    window.setFramerateLimit(60);
    
    sf::Vector2f trench(WINDOW_WIDTH, 50);

    sf::RectangleShape home_base(trench);
    home_base.setFillColor(sf::Color::Green);
    home_base.setPosition(0, WINDOW_HEIGHT - 50);

    sf::RectangleShape enemy_base(trench);
    enemy_base.setFillColor(sf::Color::Red);
    enemy_base.setPosition(0, 0);

    Button button(sf::Vector2f(250, 250 ), sf::Color::Green);
    Button button2(sf::Vector2f(350, 250 ), sf::Color::Green);
    Button button3(sf::Vector2f(450, 250 ), sf::Color::Green);

    ButtonGroup buttons;
    buttons.addButton(button);
    buttons.addButton(button2);
    buttons.addButton(button3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                //Unit* unit= new Unit(UnitType::TANK);
                shared_ptr<Unit> unit = make_shared<Unit>(Unit(UnitType::TANK));

                unit->setPosition(position.x, position.y);

                spawnedShape.push_back(unit);
            }
            
            buttons.update(event, window);
            
        }
        
            window.clear();
            window.draw(buttons);


        for (int i = 0; i < spawnedShape.size(); i++)
        {
            window.draw(*spawnedShape[i]);

            spawnedShape[i]->move_y(1);
            if (!spawnedShape[i]->is_alive())
            {
                spawnedShape.erase(spawnedShape.begin() + i);
            }
        }

        window.draw(home_base);
        window.draw(enemy_base);

        window.display();
    }

    return 0;
}


