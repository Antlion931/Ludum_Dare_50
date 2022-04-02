#include "MovingCircle.hpp"


MovingCircle::MovingCircle(sf::Vector2f position, float radius)
{
	m_local_transform.setPosition(position);
	circle.setRadius(radius);
}


void MovingCircle::onDraw(sf::RenderTarget& target)
{
	target.draw(circle,m_global_transform.getTransform());
}