#pragma once
#include <iostream>
#include <vector>

#define STANDARD_NPC 100,{0.2,0.2,0.08,1,0.0f},{5,9,13,14,14}
#define NON_MOVE_NPC 0,{0.2,0.2,0.08,1,0.0f},{1,1,4,5,5}

#include "Collision.hpp"
#include "SoundSystem.hpp"
#include "NPC.hpp"
#include "Y-sort.hpp"

class NPCCreator
{
public:
    NPCCreator(std::shared_ptr<CollisionLayer> _collisionLayer,  std::shared_ptr<std::vector<std::shared_ptr<Node>>> objectVector, std::shared_ptr<CollisionLayer> _interactionLayer);
    std::shared_ptr<NPC> makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float speed, std::vector<float> speeds, std::vector<int> indexes);
    //std::vector<std::shared_ptr<NPC>> NPCs;

private:
    std::shared_ptr<CollisionLayer> collisionLayer;
    std::shared_ptr<CollisionLayer> interactionLayer;
    std::shared_ptr<std::vector<std::shared_ptr<Node>>> objectVector;
    std::map<std::string, std::shared_ptr<TextureLoader>> textureLoaderPrototypes;
};
