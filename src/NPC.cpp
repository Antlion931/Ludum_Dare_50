#include "NPC.hpp"
#include <cmath>

NPC::NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, float _dyingTime) : 
Character(soundSystem, position, size, _speed, _dyingTime)
{
    velocity.x = std::fmod(rand(), speed * 1000.0);
    velocity.x /= 1000.0f;
    velocity.y = std::sqrt(pow(speed,2) - pow(velocity.x, 2));

    waitTime = rand()%300 / 100.0f;
    walkTime = rand()%500 / 100.0f;

    if(rand()%2)
    {
        velocity.x *= -1;
    }
    if(rand()%2)
    {
        velocity.y *= -1;
    }

    currentState = RUN;
}

void NPC::onUpdate(const sf::Time &delta)
{
    translate(scanCollisions().move_vector);
    
    currentAnimation->update(delta, isFaceingRight);
    setCorrectAnimation();

    body.setTexture(currentAnimation -> getTexture().get());
    body.setTextureRect(currentAnimation->getIntRect());

    if(currentState == RUN)
    {
        if(velocity.x > 0.0f)
        {
            isFaceingRight = true;
        }
        else
        {
            isFaceingRight = false;
        }

        translate(velocity * delta.asSeconds());

        currentTime += delta.asSeconds();
        if(currentTime >= walkTime)
        {
            currentTime = 0.0f;
            currentState = IDLE;
            velocity.x = std::fmod(rand(), speed * 1000.0);
            velocity.x /= 1000.0f;
            velocity.y = std::sqrt(pow(speed,2) - pow(velocity.x, 2));

            waitTime = rand()%500 / 100.0f;
            walkTime = rand()%500 / 100.0f;

            if(rand()%2)
            {
                velocity.x *= -1;
            }
            if(rand()%2)
            {
                velocity.y *= -1;
            }
        }
    }
    else if(currentState == IDLE)
    {
        currentTime += delta.asSeconds();

        if(currentTime >= waitTime)
        {
            currentTime = 0.0f;
            currentState = RUN;
        }
    }
    else if (currentState == DYING)
    {
        currentTime += delta.asSeconds();

        if(currentTime > dyingTime)
        {
            currentTime = 0.0f;
            currentState = DEAD;
        }
    }

    body.setPosition({-body.getSize().x/2, -body.getSize().y/2});
}