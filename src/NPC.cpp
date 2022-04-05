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
    "SEGFAULT"   
};

NPC::NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, Animation _animation, float _dyingTime) : 
Character(soundSystem, position, size, _speed, _animation, _dyingTime)
{
    //font.loadFromFile("res/Comic_Book.otf");
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

                db = std::make_shared<DialogueBox>(DialogueBox(sf::Text(RANDOM_QUOTES[dist(randomizer)],font,15)));
                addChild(db);
            }
        }
        else if(interaction_result.collider.contains("100-unit")){
            qC->sendPulse(QuestCreator::PulseType::HUG,getName());
        }
        if(db!=nullptr && db->isHidden()){
            talkable = true;
            db = nullptr;
            removeChild(db);
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
