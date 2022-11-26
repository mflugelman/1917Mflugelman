// ProyectoFinalCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    constexpr int WINDOW_WIDTH = 800;
    constexpr int WINDOW_HEIGHT = 600;

    vector<sf::Shape*> spawnedShape;


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

            if (event.type == sf::Event::MouseButtonPressed)
            {
                cout << "mose pressed" << endl;
                sf::Vector2i position = sf::Mouse::getPosition(window);
                cout << position.x << position.y;

                sf::CircleShape* circle = new sf::CircleShape(10.0f);
                circle->setPosition(position.x, position.y);
                circle->setFillColor(sf::Color::White);

                spawnedShape.push_back(circle);
            }
        }

        window.clear();

        for (int i = 0; i < spawnedShape.size(); i++)
            window.draw(*spawnedShape[i]);

        window.draw(home_base);
        window.draw(enemy_base);


        window.display();
    }


    for (int i = 0; i < spawnedShape.size(); i++)
        delete spawnedShape[i];

    return 0;
}


