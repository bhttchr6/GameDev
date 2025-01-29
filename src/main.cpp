#include <stdio.h>
#include <SFML/Graphics.hpp>

struct point2D
{
    float x;
    float y;
    point2D(): x{0.0}, y{0.0} {}
    point2D(float xin, float yin): x{xin}, y{yin}{}
};

struct circle
{
    point2D center;
    float radius;

    circle(point2D point, float r): center{point}, radius{r}{}
};

struct rectangle
{
    point2D topLeft;
    point2D topRight;
    point2D bottomLeft;
    point2D bottomRight;

};

/*
The function distance should be geenral enough to take two rectangles or two circles or circle and rectangle

template < typename T>
float minDistance(T object1, T object2)
{
    // find the point that is closest to the circle
    for(int i = 0; i < )

};
*/

sf::Vector2f newPos(sf::CircleShape &object1)
{
    sf::Vector2f POS0 = object1.getPosition();
    float X_new = POS0.x + 10.0;
    float Y_new = POS0.y + 0.0;

    return sf::Vector2f(X_new, Y_new);

}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Application Window!");
    
    // circle shape
    sf::CircleShape circle(5.0f);
    circle.setPosition(sf::Vector2f(0, 0));
    circle.move(newPos(circle));

    // rectangle shape
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100, 50));
    rectangle.setPosition(sf::Vector2f(0, 50));

    circle.setFillColor(sf::Color::Green);
    rectangle.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.draw(rectangle);
        window.display();
        
    }
    
    /*
    circle ball(point2D(), 2.0);
    
    rectangle object;
    object.bottomLeft = point2D(-1.0, 1.0);
    object.bottomRight = point2D(1.0, 1.0);
    object.topLeft = point2D(-1.0, 2.0);
    object.topRight = point2D(1.0, 2.0);

    float minDist = minDistance(ball, object);
    */
    return 0;
}