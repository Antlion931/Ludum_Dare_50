#pragma once
#include <vector>

#include "Character.hpp"

class NPC : public Character
{
private:
    float walkTime;
    float waitTime;

public:
    NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, float _dyingTime);
    void onUpdate(const sf::Time &delta) override;
};