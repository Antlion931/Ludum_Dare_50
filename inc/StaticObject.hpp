#pragma once
#include "StaticNode.hpp"

class StaticObject : public StaticNode
{
private:
    sf::RectangleShape body;

public:
    StaticObject(){};
    StaticObject(std::shared_ptr<sf::Texture> texture);
    StaticObject(std::shared_ptr<sf::Texture> texture, std::shared_ptr<CollisionLayer> collider);
    void setTexture(std::shared_ptr<sf::Texture> texture);

    void offsetTexture(sf::Vector2f offset);

protected:
    void onDraw(sf::RenderTarget &target) override;
};
