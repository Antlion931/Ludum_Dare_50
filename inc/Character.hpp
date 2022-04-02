#pragma once
#include <iostream>
#include "DynamicNode.hpp"
#include "Animation.hpp"

class Character : public DynamicNode
{
public:
    Character(sf::Vector2f position, sf::Vector2f size, float _speed);
    ~Character();

    void setIdleAnimation(std::string directoryPath, float _animationSpeed);
    void setRunAnimation(std::string directoryPath, float _animationSpeed);
    void setPunchAnimation(std::string directoryPath, float _animationSpeed);
    void setDyingAnimation(std::string directoryPath, float _animationSpeed);
    void setDeadAnimation(std::string directoryPath, float _animationSpeed);
    void kill();

    
protected:
    enum State
    {
        IDLE,
        RUN,
        PUNCH,
        DYING,
        DEAD
    };

    void onDraw(sf::RenderTarget &target) const override;

    Animation* currentAnimation;
    sf::RectangleShape body;

    void onUpdate(const sf::Time &delta) override;
    void setCorrectAnimation();

    bool isFaceingRight;
    State currentState;
    State previousState;
    float speed;

    Animation* idleAnimation;
    Animation* runAnimation;
    Animation* punchAnimation;
    Animation* dyingAnimation;
    Animation* deadAnimation;
};

