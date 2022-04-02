#pragma once
#include "DynamicNode.hpp"

class MovingCircle : public DynamicNode
{
public:
	MovingCircle(sf::Vector2f position, float radius);
	sf::CircleShape circle;
protected:
	void onDraw(sf::RenderTarget& target) const override;
};

