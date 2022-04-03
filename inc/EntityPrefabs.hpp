#pragma once
#include "StaticObject.hpp"
#include "TextureLoader.hpp"
class EntityPrefabs
{
private:
    std::shared_ptr<TextureLoader> treeTexture
        = std::make_shared<TextureLoader>(TextureLoader("./res/textures"));
public:
    std::shared_ptr<StaticObject> getStaticObject(std::string type)
    {
        
        std::shared_ptr<StaticObject> object = std::make_shared<StaticObject>();
        if(type == "tree")
        {
            object->setTexture(treeTexture->returnTexture("tree.png"));
            object->offsetTexture({-30,-30});
            object->setScale({3.f,3.f});
            object->setTranslation({0,0});
            object->setName("tree");
        }
        return object;
    }
};