#pragma once
#include "Node.hpp"
#include "Collision.hpp"

class StaticNode : public Node
{
private:
    std::shared_ptr<CollisionLayer> player_interaction_layer;

public:
    StaticNode(){};
    StaticNode(std::shared_ptr<CollisionLayer> collider);
    void setCollider(std::shared_ptr<CollisionLayer> collider);

protected:    
    virtual void onUpdate(const sf::Time &delta) override;
};