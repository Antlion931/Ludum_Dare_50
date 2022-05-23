#include "NPC.hpp"
#include <cmath>
#include <random>

std::vector<std::string> const RANDOM_QUOTES = {
    "Hey",
    "Hello",
    "Bonjour",
    "Hi",
    "M'lady",
    "42", 
    "NULL REFERENCE",
    "SEGFAULT",
    "How is your day?",
    "How are you?",
    "Thanks",
    "Good morning"
};

NPC::NPC(sf::Vector2f position, std::string animationDirectoryName, float idleTime, float dyingTime, float deadTime, float runTime, float _speed) : 
GameObject(position, animationDirectoryName, idleTime, dyingTime, deadTime), speed(_speed)
{
    animationManager.addAnimation(RUN, runTime);
    randomVelocityAndTimes();
}

void NPC::onUpdate(const sf::Time &delta)
{
    if(dot(velocity, velocity) > 0.0f)
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
            animationManager.play(IDLE);
            velocity.x = 0.0f;
            velocity.y = 0.0f;
        }
    }
    else if(!dying && !dead)
    {
        currentTime += delta.asSeconds();

        if(currentTime >= waitTime)
        {
            currentTime = 0.0f;
            animationManager.play(RUN);
            randomVelocityAndTimes();
        }
    }

    auto interaction_result = scanCollisions("INTERACTION");
    if(!dead){
        if (interaction_result.collider.contains("KILL"))
        {   
            if(!dead){
                qC->sendPulse(QuestCreator::PulseType::KILL,getName());
                dead = true;
                kill();
            }
        }
        else if(interaction_result.collider.contains("TALK")){
            if(talkable){
                qC->sendPulse(QuestCreator::PulseType::TALK,getName());
                talkable = false;
                auto randomizer = std::random_device();
                auto dist = std::uniform_int_distribution(0, (int)(RANDOM_QUOTES.size() - 1));

                db = std::make_shared<DialogueBox>(DialogueBox(sf::Text(RANDOM_QUOTES[dist(randomizer)],font,64)));
                addChild(db);
            }
        }
        else if(interaction_result.collider.contains("100-unit")){
            qC->sendPulse(QuestCreator::PulseType::HUG,getName());
        }
        if(db!=nullptr && db->isHidden()){
            talkable = true;
            removeChild(db);
            db = nullptr;
        }
    }
    updateBody(delta);
}

void NPC::randomVelocityAndTimes()
{
    if(speed > 0.0f)
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
}
