#include "NPCCreator.hpp"

NPCCreator::NPCCreator(std::shared_ptr<CollisionLayer>& _collisionLayer, std::vector<std::shared_ptr<Node>>& _objectVector, std::shared_ptr<CollisionLayer>& _interactionLayer) 
    : collisionLayer(_collisionLayer), objectVector(_objectVector), interactionLayer(_interactionLayer)
{}

NPC& NPCCreator::makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float speed, std::vector<float> speeds, std::vector<int> indexes)
{
    auto npc = std::make_shared<NPC>(NPC(soundSystem, position, size, speed, Animation("./res/textures/npc/" + NPCName, speeds, indexes), 0.32));
    //NPCs.push_back(npc);
    npc->setName(NPCName);
    npc->setDyingSoundName("dead.wav");
    npc->addCollider(nullptr, collisionLayer, {0.0, 35.0}, 15.0);
    npc->addCollider(nullptr, interactionLayer, {0.0, 35.0}, 40.0);
    objectVector.push_back(npc);
    return *npc.get();
}
