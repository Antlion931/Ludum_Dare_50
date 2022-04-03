#include "NPCCreator.hpp"

NPCCreator::NPCCreator(std::shared_ptr<CollisionLayer>& _collisionLayer, std::shared_ptr<YSort>& _ysort, std::shared_ptr<CollisionLayer>& _interactionLayer) : collisionLayer(_collisionLayer), ysort(_ysort), interactionLayer(_interactionLayer)
{}

void NPCCreator::makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size)
{
    NPCs.push_back(std::make_shared<NPC>(NPC(soundSystem, position, size, 100, 0.12, interactionLayer)));
    NPCs.back()->setUpByName(NPCName);
    NPCs.back()->addCollider(collisionLayer, {0.0, 35.0}, 15.0);
    ysort->addChild(NPCs.back());
}