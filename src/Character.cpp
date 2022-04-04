#include <cmath>
#include <iostream>
#include "Character.hpp"
#include "Animation.hpp"
#include "SoundSystem.hpp"

Character::Character(SoundSystem& _soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, Animation _animation, float _dyingTime) : 
soundSystem(_soundSystem), speed(_speed), body(size), animation(_animation), dyingTime(_dyingTime)
{
    body.setSize({_animation.getIntRect().width, _animation.getIntRect().height});
    setTranslation(position);
    body.setPosition({-body.getSize().x/2, -body.getSize().y/2});
    currentTime = 0.0f;
}

void Character::onUpdate(const sf::Time &delta)
{
    if(velocity.x != 0.0f || velocity.y != 0.0f)
    {
        animation.changeAnimation(RUN);
        
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
        animation.changeAnimation(IDLE);
    }

    updateBody(delta);
}

void Character::offsetTexture(sf::Vector2f offset)
{
    body.setPosition({body.getPosition().x + offset.x, body.getPosition().y + offset.y});
}


void Character::kill()
{
    if(animation.getCurrentAnimation() != DEAD && animation.getCurrentAnimation() != DYING)
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        currentTime = 0.0f;
        animation.changeAnimation(DYING);
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
    translate(scanCollisions("COLLISION").move_vector);
    animation.update(delta, isFaceingRight); 

    body.setTexture(animation.getTexture().get());
    body.setTextureRect(animation.getIntRect());
}

bool Character::isDead()
{
    if(animation.getCurrentAnimation() == DEAD || animation.getCurrentAnimation() == DYING)
    {
        return true;
    } 
    return false;
}
