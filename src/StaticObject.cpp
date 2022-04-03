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
    body.setSize({texture.get()->getSize().x,texture.get()->getSize().y});
}


void StaticObject::offsetTexture(sf::Vector2f offset)
{
    body.setPosition({body.getPosition().x + offset.x, body.getPosition().y + offset.y});
}


void StaticObject::onDraw(sf::RenderTarget &target)
{
    //sf::Vector2u transformVector = {getGlobalTransform().getScale().x,getGlobalTransform().getScale().y};
    //body.setSize({body.getSize().x * transformVector.x, body.getSize().y *  transformVector.y});
    target.draw(body,m_global_transform.getTransform());
}