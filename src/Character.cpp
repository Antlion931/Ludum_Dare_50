#include <cmath>
#include <iostream>
#include "Character.hpp"
#include "Animation.hpp"

Character::Character(sf::Vector2f position, float radius, float _speed) : MovingCircle(position, radius), speed(_speed)
{
    currentState = IDLE;
    previousState = IDLE;
    idleAnimation = nullptr;
    runAnimation = nullptr;
    punchAnimation = nullptr;
    sitAnimation = nullptr;
    deadAnimation = nullptr;
    currentAnimation = nullptr;
}

Character::~Character()
{
    delete idleAnimation;
    delete runAnimation;
    delete punchAnimation;
    delete sitAnimation;
    delete deadAnimation;
}

bool Character::isColidedWith(sf::CircleShape _circle)
{
    float distanceBetween = std::sqrt(std::pow(circle.getPosition().x - circle.getPosition().x, 2)  + std::pow(circle.getPosition().y - circle.getPosition().y, 2));

    if(distanceBetween <= circle.getRadius() + _circle.getRadius())
    {
        return true;
    }
    return false;
}

void Character::setIdleAnimation(std::string directoryPath, float _animationSpeed)
{
    idleAnimation = new Animation(directoryPath, _animationSpeed);
    currentAnimation = idleAnimation;
}

void Character::setRunAnimation(std::string directoryPath, float _animationSpeed)
{
    runAnimation = new Animation(directoryPath, _animationSpeed);
}

void Character::setSitAnimation(std::string directoryPath, float _animationSpeed)
{
    sitAnimation =  new Animation(directoryPath, _animationSpeed);
}

void Character::setPunchAnimation(std::string directoryPath, float _animationSpeed)
{
    punchAnimation = new Animation(directoryPath, _animationSpeed);
}

void Character::setDeadAnimation(std::string directoryPath, float _animationSpeed)
{
    deadAnimation = new Animation(directoryPath, _animationSpeed);
}

void Character::onUpdate(const sf::Time &delta)
{
    translate({velocity.x * delta.asSeconds() , velocity.y * delta.asSeconds()});
    
    if(velocity.x != 0.0f || velocity.y != 0.0f)
    {
        currentState = RUN;
        
        if(velocity.x > 0.0f)
        {
            isFaceingRight = true;
        }
        else if(velocity.x < 0.0f)
        {
            isFaceingRight = false;
        }
    }
    else
    {
        currentState = IDLE;
    }

    setCorrectAnimation();
    currentAnimation->update(delta, isFaceingRight); 
    circle.setTexture(currentAnimation -> getTexture());
}

void Character::setCorrectAnimation()
{
    if(currentState != previousState)
    {
        previousState = currentState;
        switch(currentState)
        {
            case IDLE:
                currentAnimation = idleAnimation;
            break;

            case RUN:
                currentAnimation = runAnimation;
            break;

            case SIT:
                currentAnimation = sitAnimation;
            break;

            case PUNCH:
                currentAnimation = punchAnimation;
            break;

            case DEAD:
                currentAnimation = deadAnimation;
            break;
        }

        currentAnimation->reset();
    }
}
