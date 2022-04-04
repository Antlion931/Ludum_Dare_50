#pragma once
#include <vector>

#include "Character.hpp"
#include"DialogueBox.hpp"

class NPC : public Character
{
private:
    float walkTime;
    float waitTime;
    bool talkable = true;
    bool dead = false;
    std::shared_ptr<CollisionLayer> player_interaction_layer;

    void onUpdate(const sf::Time &delta) override;
    void randomVelocityAndTimes();
    sf::Font font;
    std::shared_ptr<DialogueBox> db = nullptr;

public:
    NPC(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, Animation, float _dyingTime, std::shared_ptr<CollisionLayer> _player_interaction_layer);
    void setUpByName(std::string name);
};