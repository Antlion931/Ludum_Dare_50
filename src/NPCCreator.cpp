#include "NPCCreator.hpp"

NPCCreator::NPCCreator(std::shared_ptr<CollisionLayer> _collisionLayer,  std::shared_ptr<std::vector<std::shared_ptr<Node>>> _objectVector, std::shared_ptr<CollisionLayer> _interactionLayer) 
{
    collisionLayer = _collisionLayer;
    objectVector = _objectVector;
    interactionLayer = _interactionLayer;
    textureLoaderPrototypes["Male"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Male"));
    textureLoaderPrototypes["Tree"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Tree"));
    textureLoaderPrototypes["Building"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Building"));
    textureLoaderPrototypes["Bench_Down"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Bench_Down"));
    textureLoaderPrototypes["Pot"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Pot"));
    textureLoaderPrototypes["Hydrant"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Hydrant"));
    textureLoaderPrototypes["Umbrella"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Umbrella"));
    textureLoaderPrototypes["Female"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Female"));
    textureLoaderPrototypes["Bush"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Bush"));
    textureLoaderPrototypes["Chair_Left"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Chair_Left"));
    textureLoaderPrototypes["Chair_Right"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Chair_Right"));
    textureLoaderPrototypes["Flowers"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Flowers"));
    textureLoaderPrototypes["Lamp_Left"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Lamp_Left"));
    textureLoaderPrototypes["Lamp_Right"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Lamp_Right"));
    textureLoaderPrototypes["Shop"] = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Shop"));
}

std::shared_ptr<NPC> NPCCreator::makeNPC(std::string NPCName, SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float speed, std::vector<float> speeds, std::vector<int> indexes)
{
    //std::cout << NPCName << std::endl;
    auto npc = std::make_shared<NPC>(NPC(soundSystem, position, size, speed, Animation(textureLoaderPrototypes[NPCName], speeds, indexes), 0.4));
    //NPCs.push_back(npc);
    npc->setName(NPCName);
    npc->setDyingSoundName("dead.wav");
    //npc->addCollider(nullptr, collisionLayer, {0.0, 35.0}, 15.0, "COLLISION");
    //npc->addCollider(nullptr, interactionLayer, {0.0, 35.0}, 40.0, "INTERACTION");
    objectVector->push_back(npc);
    return npc;
}
