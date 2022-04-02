#include <cmath>
#include "Character.hpp"

Character::Character(sf::Vector2f position, float radius, float _speed) : MovingCircle(position, radius), speed(_speed)
{}

bool Character::isColidedWith(sf::CircleShape _circle)
{
    float distanceBetween = std::sqrt(std::pow(circle.getPosition().x - circle.getPosition().x, 2)  + std::pow(circle.getPosition().y - circle.getPosition().y, 2));

    if(distanceBetween <= circle.getRadius() + _circle.getRadius())
    {
        return true;
    }
    return false;
}