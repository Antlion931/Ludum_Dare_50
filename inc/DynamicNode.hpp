#pragma once
#include "Container.hpp"
class DynamicNode : public Node
{
protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

public:
	void setVelocity(sf::Vector2f _velocity);
	sf::Vector2f getVelocity();

protected:
	virtual void onDraw(sf::RenderTarget& target) const override{};
	virtual void onUpdate(const sf::Time &delta) override;
};

