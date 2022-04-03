#pragma once
#include <iostream>
#include <vector>

#include "Container.hpp"
#include "Collision.hpp"
#include "SoundSystem.hpp"
#include "NPC.hpp"
#include "Y-sort.hpp"

class NPCContainer : public Container
{
public:
    NPCContainer(std::shared_ptr<CollisionLayer> _collision, std::shared_ptr<YSort> ysort);
    void makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size);
private:
    std::shared_ptr<CollisionLayer> collision;
    std::shared_ptr<YSort> ysort;
    std::vector<std::shared_ptr<NPC>> NPCs;
};
