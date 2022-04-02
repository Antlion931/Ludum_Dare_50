#include <cmath>
#include <iostream>
#include "Character.hpp"
#include "Animation.hpp"

Character::Character(sf::Vector2f position, sf::Vector2f size, float _speed) : speed(_speed), body(size)
{
    currentState = IDLE;
    previousState = IDLE;
    idleAnimation = nullptr;
    runAnimation = nullptr;
    punchAnimation = nullptr;
    deadAnimation = nullptr;
    currentAnimation = nullptr;
    body.setPosition(position);
}

Character::~Character()
{
}

void Character::setIdleAnimation(std::string directoryPath, float _animationSpeed)
{
    idleAnimation = std::make_shared<Animation>(Animation(directoryPath, _animationSpeed));
    currentAnimation = idleAnimation;
}

void Character::setRunAnimation(std::string directoryPath, float _animationSpeed)
{
    runAnimation = std::make_shared<Animation>(Animation(directoryPath, _animationSpeed));
}

void Character::setPunchAnimation(std::string directoryPath, float _animationSpeed)
{
    punchAnimation = std::make_shared<Animation>(Animation(directoryPath, _animationSpeed));
}

void Character::setDeadAnimation(std::string directoryPath, float _animationSpeed)
{
    deadAnimation = std::make_shared<Animation>(Animation(directoryPath, _animationSpeed));
}

void Character::setDyingAnimation(std::string directoryPath, float _animationSpeed)
{
    dyingAnimation = std::make_shared<Animation>(Animation(directoryPath, _animationSpeed));
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

    body.setTexture(currentAnimation -> getTexture().get());
    body.setTextureRect(currentAnimation->getIntRect());
}

void Character::setCorrectAnimation()
{

    //std::cout << currentState << std::endl;

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

            case PUNCH:
                currentAnimation = punchAnimation;
            break;

            case DYING:
                currentAnimation = dyingAnimation;
            break;

            case DEAD:
                currentAnimation = deadAnimation;
            break;
        }

        currentAnimation->reset();
    }
}

void Character::kill()
{
    if(currentState != DEAD)
    {
        currentState = DYING;
    }
}

void Character::onDraw(sf::RenderTarget &target) const
{
    target.draw(body,m_global_transform.getTransform());
}
