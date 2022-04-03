#include "StaticObject.hpp"

StaticObject::StaticObject(std::shared_ptr<sf::Texture> texture)
{
    setTexture(texture);
}


StaticObject::StaticObject(std::shared_ptr<sf::Texture> texture, std::shared_ptr<CollisionLayer> collider)
{
    setTexture(texture);
    //setCollider(collider);
}


void StaticObject::setTexture(std::shared_ptr<sf::Texture> texture)
{
    body.setTexture(texture.get());
}