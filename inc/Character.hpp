#pragma once
#include <iostream>
#include "MovingCircle.hpp"
#include "Animation.hpp"

class Character : public MovingCircle
{
public:
    bool isColidedWith(sf::CircleShape _circle);
    Character(sf::Vector2f position, float radius, float _speed);
    ~Character();

    void setIdleAnimation(std::string directoryPath, float _animationSpeed);
    void setRunAnimation(std::string directoryPath, float _animationSpeed);
    void setSitAnimation(std::string directoryPath, float _animationSpeed);
    void setPunchAnimation(std::string directoryPath, float _animationSpeed);
    void setDeadAnimation(std::string directoryPath, float _animationSpeed);

protected:
    enum State
    {
        IDLE,
        RUN,
        SIT,
        PUNCH,
        DEAD
    };


    Animation* currentAnimation;

    void onUpdate(const sf::Time &delta) override;
    void setCorrectAnimation();

    bool isFaceingRight;
    State currentState;
    State previousState;
    float speed;

    Animation* idleAnimation;
    Animation* runAnimation;
    Animation* sitAnimation;
    Animation* punchAnimation;
    Animation* deadAnimation;
};

