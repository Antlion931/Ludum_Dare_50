#pragma once
#include "NPC.hpp"
#include "TextureLoader.hpp"
class EntityPrefabs
{
private:
    std::shared_ptr<TextureLoader> treeTexture
        = std::make_shared<TextureLoader>(TextureLoader("./res/textures/npc/Tree"));
public:
    std::shared_ptr<NPC> getStaticObject(std::string type)
    {
        
        /*std::shared_ptr<NPC> object = std::make_shared<NPC>();
        if(type == "tree")
        {
            object->setTexture(treeTexture->returnTexture("tree.png"));
            object->offsetTexture({-13,-30});
            object->setScale({3.f,3.f});
            object->setName("tree");
            //object->setActive(0);
            //object->setVisible(0);
        }
        return object;*/
    }
};