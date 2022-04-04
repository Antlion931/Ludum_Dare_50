#include "NPCCreator.hpp"

NPCCreator::NPCCreator(std::shared_ptr<CollisionLayer>& _collisionLayer, std::vector<std::shared_ptr<Node>>& _objectVector, std::shared_ptr<CollisionLayer>& _interactionLayer) 
    : collisionLayer(_collisionLayer), objectVector(_objectVector), interactionLayer(_interactionLayer)
{}

void NPCCreator::makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size)
{
    NPCs.push_back(std::make_shared<NPC>(NPC(soundSystem, position, size, 100, Animation("./res/textures/npc/" + NPCName, {0.2, 0.2, 0.08, 1, 0.0f}, {5, 9, 13, 14, 14}), 0.32)));
    NPCs.back()->setName(NPCName);
    NPCs.back()->setDyingSoundName("dead.wav");
    NPCs.back()->addCollider(nullptr, collisionLayer, {0.0, 35.0}, 15.0);
    NPCs.back()->addCollider(nullptr, interactionLayer, {0.0, 35.0}, 40.0);
    objectVector.push_back(NPCs.back());
}
