#include <cmath>
#include <iostream>
#include "Character.hpp"
#include "Animation.hpp"
#include "SoundSystem.hpp"

Character::Character(SoundSystem& _soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, float _dyingTime) : 
soundSystem(_soundSystem), speed(_speed), body(size), dyingTime(_dyingTime)
{
    currentState = IDLE;
    previousState = IDLE;
    idleAnimation = nullptr;
    runAnimation = nullptr;
    punchAnimation = nullptr;
    deadAnimation = nullptr;
    currentAnimation = nullptr;
    setTranslation(position);
    currentTime = 0.0f;
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

    updateBody(delta);
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
    if(currentState != DEAD && currentState != DYING)
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        currentTime = 0.0f;
        currentState = DYING;
        soundSystem.playSound(dyingSoundName);
    }
}

void Character::onDraw(sf::RenderTarget &target)
{
    target.draw(body,getGlobalTransform().getTransform());
}

void Character::setDyingSoundName(std::string _dyingSoundName)
{
    dyingSoundName = _dyingSoundName;
}

void Character::updateBody(const sf::Time&  delta)
{
    translate({velocity.x * delta.asSeconds() , velocity.y * delta.asSeconds()});
    translate(scanCollisions().move_vector);
    setCorrectAnimation();
    currentAnimation->update(delta, isFaceingRight); 

    body.setTexture(currentAnimation -> getTexture().get());
    body.setTextureRect(currentAnimation->getIntRect());
    body.setPosition({-body.getSize().x/2, -body.getSize().y/2});
}
