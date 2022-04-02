#pragma once
#include "Collision.hpp"

class DynamicNode : public Collidable
{
public:
	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	void setVelocity(sf::Vector2f _velocity);
	sf::Vector2f getVelocity();

protected:
	virtual void onDraw(sf::RenderTarget& target) const override{};
	virtual void onUpdate(const sf::Time &delta) override;
};

