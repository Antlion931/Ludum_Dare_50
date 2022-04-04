#include "NPC.hpp"
#include <cmath>

NPC::NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, Animation _animation, float _dyingTime) : 
Character(soundSystem, position, size, _speed, _animation, _dyingTime)
{
    randomVelocityAndTimes();
    animation.changeAnimation(RUN);
}

void NPC::onUpdate(const sf::Time &delta)
{
    if(animation.getCurrentAnimation() == RUN)
    {
        if(velocity.x > 0.0f)
        {
            isFaceingRight = true;
        }
        else
        {
            isFaceingRight = false;
        }

        currentTime += delta.asSeconds();
        if(currentTime >= walkTime)
        {
            currentTime = 0.0f;
            animation.changeAnimation(IDLE);
            velocity.x = 0.0f;
            velocity.y = 0.0f;
        }
    }
    else if(animation.getCurrentAnimation() == IDLE)
    {
        currentTime += delta.asSeconds();

        if(currentTime >= waitTime)
        {
            currentTime = 0.0f;
            animation.changeAnimation(RUN);
            randomVelocityAndTimes();
        }
    }
    else if (animation.getCurrentAnimation() == DYING)
    {
        currentTime += delta.asSeconds();

        if(currentTime > dyingTime)
        {
            currentTime = 0.0f;
            animation.changeAnimation(DEAD);
        }
    }
    
    auto interaction_result = scanCollisions(1);
    if (interaction_result.collider != nullptr && interaction_result.collider->getName() == "kill-box")
    {
        kill();
    }

    updateBody(delta);
}

void NPC::randomVelocityAndTimes()
{
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
