#include "NPCContainer.hpp"

NPCContainer::NPCContainer(std::shared_ptr<CollisionLayer> _collision, std::shared_ptr<YSort> _ysort) : collision(_collision), ysort(_ysort)
{}

void NPCContainer::makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size)
{
    NPCs.push_back(std::make_shared<NPC>(NPC(soundSystem, position, size, 100, 1)));
    NPCs.back()->setUpByName(NPCName);
    NPCs.back()->setCollider(collision, {0.0, 25.0}, 30.0);
    addChild(NPCs.back());
    ysort->addChild(NPCs.back());
}