#include "StaticNode.hpp"
#include <Collision.hpp>

StaticNode::StaticNode(std::shared_ptr<CollisionLayer> collider)
{

}


void StaticNode::onUpdate(const sf::Time &delta)
{
    /*auto interaction_result = scanCollisions(0, player_interaction_layer);
    if (interaction_result.collider != nullptr && interaction_result.collider->getName() == "kill-box")
    {
        //
    }*/
}