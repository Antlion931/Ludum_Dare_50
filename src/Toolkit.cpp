#include <SFML/Graphics.hpp>
#include <cmath>

#include "Toolkit.hpp"

bool clamp(sf::RectangleShape a, sf::Vector2f b)
{
	sf::Vector2f size = a.getSize();
	size.x *= a.getScale().x;
	size.y *= a.getScale().y;
	sf::Vector2f position = a.getPosition();

	return b.x <= position.x + size.x &&
		   b.x >= position.x &&
		   b.y <= position.y + size.y &&
		   b.y >= position.y;
}


bool clamp(sf::RectangleShape a, sf::Vector2i b)
{
	sf::Vector2f size = a.getSize();
	size.x *= a.getScale().x;
	size.y *= a.getScale().y;
	sf::Vector2f position = a.getPosition();

	return b.x <= position.x + size.x &&
		b.x >= position.x &&
		b.y <= position.y + size.y &&
		b.y >= position.y;
}

sf::Vector2f dot(const sf::Vector2f a, const sf::Vector2f b)
	{
		sf::Vector2f result;
		result.x = a.x * b.x;
		result.y = a.y * b.y;
		return result;
	}

sf::Transformable combineTransforms(const sf::Transformable &parent, const sf::Transformable &child)
{
	sf::Transformable result;
	result.setScale(dot(parent.getScale(),child.getScale()));
	result.setRotation(parent.getRotation() + child.getRotation());
	result.setPosition(parent.getTransform() * child.getPosition());
	return result;
}

std::ostream& operator<< (std::ostream& out, sf::Vector2f const& vec)
{
	return out << vec.x << " " << vec.y;
}

float length(const sf::Vector2f a) 
{
	return std::sqrt(a.x * a.x + a.y * a.y);
}

sf::Vector2f norm(const sf::Vector2f a)
{
	return a / length(a);
}