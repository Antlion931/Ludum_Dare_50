#include "DynamicNode.hpp"

void DynamicNode::setVelocity(sf::Vector2f _velocity)
{
	velocity = _velocity;
}
sf::Vector2f DynamicNode::getVelocity()
{
	return velocity;
}

void DynamicNode::onUpdate(const sf::Time &delta)
{
	translate({velocity.x * delta.asSeconds() , velocity.y * delta.asSeconds()});
}