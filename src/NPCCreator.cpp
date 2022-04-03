#include "NPCCreator.hpp"

NPCCreator::NPCCreator(std::shared_ptr<CollisionLayer>& _collisionLayer, std::shared_ptr<YSort>& _ysort) : collisionLayer(_collisionLayer), ysort(_ysort)
{}

void NPCCreator::makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size)
{
    NPCs.push_back(std::make_shared<NPC>(NPC(soundSystem, position, size, 100, Animation("./res/textures/npc/" + NPCName, {0.1, 0.2, 0.08, 1, 0.0f}, {5, 9, 13, 14, 14}), 0.32)));
    NPCs.back()->setName(NPCName);
    NPCs.back()->setDyingSoundName("dead.wav");
    NPCs.back()->setCollider(collisionLayer, {0.0, 35.0}, 15.0);
    ysort->addChild(NPCs.back());
}
