#include <SFML/Graphics.hpp>

struct world
{
     static constexpr float accGrav = 1.0;
     static constexpr float e = 0.5;

};

/*
The function distance should be geenral enough to take two rectangles or two circles or circle and rectangle
*/
template < typename T1, typename T2>
bool collison(T1 &object1, T2 &object2)
{
    // find the point that is closest to the circle
    sf::Vector2f posObj1 = object1.getPosition();
    sf::Vector2f posObj2 = object2.getPosition();

    if(posObj1.y + object1.getRadius() > posObj2.y)
    {
        return true;
    }
    else
    {
        return false;
    }

    

};

float GetVelocity(float initalVelocity, float time)
{
    return  initalVelocity + world::accGrav * time;
};

sf::Vector2f newPos(sf::CircleShape &object1 , float time, float initialVelocity)
{
    sf::Vector2f POS0 = object1.getPosition();
    
    float X_new = POS0.x + 0.0;
    float Y_new = POS0.y + initialVelocity * time + 0.5 * world::accGrav * time * time;


    return sf::Vector2f(X_new, Y_new);

}
