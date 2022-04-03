#include "NPC.hpp"
#include <cmath>

NPC::NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, float _dyingTime) : 
Character(soundSystem, position, size, _speed, _dyingTime)
{
    randomVelocityAndTimes();
    currentState = RUN;
}

void NPC::onUpdate(const sf::Time &delta)
{
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

        currentTime += delta.asSeconds();
        if(currentTime >= walkTime)
        {
            currentTime = 0.0f;
            currentState = IDLE;
            velocity.x = 0.0f;
            velocity.y = 0.0f;
        }
    }
    else if(currentState == IDLE)
    {
        currentTime += delta.asSeconds();

        if(currentTime >= waitTime)
        {
            currentTime = 0.0f;
            randomVelocityAndTimes();
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

void NPC::setUpByName(std::string name)
{
    setName(name);
    setRunAnimation("./res/textures/npc/" + name + "/Run", 0.1);
    setIdleAnimation("./res/textures/npc/" + name + "/Idle", 0.2);
    setDyingAnimation("./res/textures/npc/" + name + "/Dying", 1);
    setDeadAnimation("./res/textures/npc/" + name + "/Dead", 1);
    setDyingSoundName("dead.wav");
}
