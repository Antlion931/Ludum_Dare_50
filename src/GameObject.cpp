#include <cmath>
#include <iostream>
#include "GameObject.hpp"
#include "AnimationManager.hpp"
#include "SoundSystem.hpp"

GameObject::GameObject(sf::Vector2f position, std::string animationDirectoryName, float idleTime, float dyingTime, float deadTime) :
animationManager(animationDirectoryName, { {IDLE,idleTime}, {DYING,dyingTime}, {DEAD,deadTime} }, IDLE)
{
    soundSystem = SoundSystem::getInstance();

    body.setSize({animationManager.getIntRect().width, animationManager.getIntRect().height});
    setTranslation(position);
    body.setPosition({-body.getSize().x/2, -body.getSize().y/2});
}

void GameObject::onUpdate(const sf::Time &delta)
{
    updateBody(delta);
}

void GameObject::offsetTexture(sf::Vector2f offset)
{
    body.setPosition({body.getPosition().x + offset.x, body.getPosition().y + offset.y});
}

void GameObject::kill()
{
    if(!dying && !dead)
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        dying = true;
        animationManager.setDefault(DEAD);
        animationManager.playOnce(DYING);
        soundSystem->playSound(dyingSoundName);
    }
}

void GameObject::onDraw(sf::RenderTarget &target)
{
    target.draw(body,getGlobalTransform().getTransform());
}

void GameObject::setDyingSoundName(std::string _dyingSoundName)
{
    dyingSoundName = _dyingSoundName;
}

void GameObject::updateBody(const sf::Time&  delta)
{
    translate({velocity.x * delta.asSeconds() , velocity.y * delta.asSeconds()});
    translate(scanCollisions("COLLISION").move_vector);
    animationManager.update(delta, isFaceingRight); 

    body.setTexture(animationManager.getTexture().get());
    body.setTextureRect(animationManager.getIntRect());
}

bool GameObject::isDead()
{
    return dead;
}
