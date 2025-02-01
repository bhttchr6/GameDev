#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.hpp"



int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Application Window!");
    
    // circle shape
    sf::CircleShape circle(10.0f);
    circle.setPosition(sf::Vector2f(10, 0));

    float time = 0.0;
    
    // rectangle shape
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setPosition(sf::Vector2f(0, 400));

    circle.setFillColor(sf::Color::Green);
    rectangle.setFillColor(sf::Color::Red);

    
    int dir = 1;
    float dt = 0.5;
    float iniVel = 0.0;
    while (window.isOpen())
    {
        time = time + dt;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        std::cout << time << std::endl;
        //Move the circle continuously
        circle.setPosition(newPos(circle, time, iniVel));
        if(collison(circle, rectangle))
        {
            //throw std::runtime_error("collision detected");
            float finalVelocity = GetVelocity(iniVel, time);
            iniVel = world::e * finalVelocity;

        }
        window.clear();
        window.draw(circle);
        window.draw(rectangle);
        window.display();

        sf::sleep(sf::milliseconds(100)); // Slow down movement for visibility
        
    
    }
    
    
    
    return 0;
}