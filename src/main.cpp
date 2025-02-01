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

    // rectangle shape
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setPosition(sf::Vector2f(0, 400));

    circle.setFillColor(sf::Color::Green);
    rectangle.setFillColor(sf::Color::Red);

    
    int dir = 1;
    float dt = 0.5;
    float iniVel = 0.0;
    float time = 0.0;
    bool impact = false;
    float localTime = 0.0;
   
    while (window.isOpen())
    {
        time = time + localTime;
        localTime = localTime + dt;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        //Move the circle continuously
        circle.setPosition(newPos(circle, localTime, iniVel));
        
        if(collison(circle, rectangle))
        {
            //throw std::runtime_error("collision detected");
            impact = true;
            // get final velocity of ball at time of collision
            float finalVelocity = GetVelocity(iniVel, localTime);
            std::cout << "velocity at collision = " << finalVelocity << std::endl;

            //The initial velocity of ball = -e * final velocity of ball
            iniVel = -1 * world::e * finalVelocity;

            //correct ball position
            sf::Vector2f posCurr = circle.getPosition();
            circle.setPosition(sf::Vector2f(posCurr.x, posCurr.y - circle.getRadius()));

            //revert local time to 0
            localTime = 0.0 ;

            

        }
        window.clear();
        window.draw(circle);
        window.draw(rectangle);
        window.display();

        sf::sleep(sf::milliseconds(100)); // Slow down movement for visibility
        
    
    }
    
    
    
    return 0;
}