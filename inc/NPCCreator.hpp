#pragma once
#include <iostream>
#include <vector>

#include "Collision.hpp"
#include "SoundSystem.hpp"
#include "NPC.hpp"
#include "Y-sort.hpp"

class NPCCreator
{
public:
    NPCCreator(std::shared_ptr<CollisionLayer>& _collisionLayer, std::shared_ptr<YSort>& ysort);
    void makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size);
private:
    std::shared_ptr<CollisionLayer>& collisionLayer;
    std::shared_ptr<YSort>& ysort;
    std::vector<std::shared_ptr<NPC>> NPCs;
};
