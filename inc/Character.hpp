#pragma once
#include <iostream>
#include <memory>
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

    void onDraw(sf::RenderTarget &target) override;

    std::shared_ptr<Animation> currentAnimation;
    sf::RectangleShape body;

    void onUpdate(const sf::Time &delta) override;
    void setCorrectAnimation();

    bool isFaceingRight;
    State currentState;
    State previousState;
    float speed;

    std::shared_ptr<Animation> idleAnimation;
    std::shared_ptr<Animation> runAnimation;
    std::shared_ptr<Animation> punchAnimation;
    std::shared_ptr<Animation> dyingAnimation;
    std::shared_ptr<Animation> deadAnimation;
};

