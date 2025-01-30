#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "utils.hpp"


int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Application Window!");
    
    // circle shape
    sf::CircleShape circle(5.0f);
    circle.setPosition(sf::Vector2f(10, 0));
    
    

    // rectangle shape
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(300, 50));
    rectangle.setPosition(sf::Vector2f(0, 400));

    circle.setFillColor(sf::Color::Green);
    rectangle.setFillColor(sf::Color::Red);

    
    int dir = 1;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //Move the circle continuously
        circle.setPosition(newPos(circle, dir));
        if(collison(circle, rectangle))
        {
            //throw std::runtime_error("collision detected");
            dir = - dir;

        }
        window.clear();
        window.draw(circle);
        window.draw(rectangle);
        window.display();

        sf::sleep(sf::milliseconds(100)); // Slow down movement for visibility
        
    
    }
    
    
    
    return 0;
}