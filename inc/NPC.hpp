#pragma once
#include <vector>

#include "Character.hpp"

class NPC : public Character
{
private:
    float walkTime;
    float waitTime;
    void onUpdate(const sf::Time &delta) override;
    void randomVelocityAndTimes();

public:
    NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, Animation, float _dyingTime);
};