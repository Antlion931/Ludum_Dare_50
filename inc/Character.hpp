#pragma once
#include "MovingCircle.hpp"

class Character : public MovingCircle
{
public:
    bool isColidedWith(sf::CircleShape _circle);
    Character(sf::Vector2f position, float radius, float _speed);

protected:
    enum state
    {
        IDLE,
        RUN,
        SIT,
        PUNCH,
        DEAD
    };

    float speed;
    bool isFaceingRight;
};
