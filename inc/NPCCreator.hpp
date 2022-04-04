#pragma once
#include <iostream>
#include <vector>

#include "Collision.hpp"
#include "SoundSystem.hpp"
#include "NPC.hpp"
#include "Y-sort.hpp"
#include "AnimationSequences.hpp"

class NPCCreator
{
public:
    NPCCreator(std::shared_ptr<CollisionLayer> _collisionLayer, std::vector<std::shared_ptr<Node>>& objectVector, std::shared_ptr<CollisionLayer> _interactionLayer);
    std::shared_ptr<NPC> makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, std::vector<float> speeds, std::vector<int> indexes);
    //std::vector<std::shared_ptr<NPC>> NPCs;

private:
    std::shared_ptr<CollisionLayer> collisionLayer;
    std::shared_ptr<CollisionLayer>& interactionLayer;
    std::vector<std::shared_ptr<Node>> objectVector;
};
