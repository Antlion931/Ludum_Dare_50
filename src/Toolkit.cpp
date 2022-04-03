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

float dot(const sf::Vector2f a, const sf::Vector2f b)
{
	return a.x*b.x + a.y*b.y;
}

sf::Transformable combineTransforms(const sf::Transformable &parent, const sf::Transformable &child)
{
	sf::Transformable result;
	result.setScale({parent.getScale().x*child.getScale().x,parent.getScale().y*child.getScale().y});
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

float length_squared(const sf::Vector2f a) 
{
	return a.x * a.x + a.y * a.y;
}

float clamp(float a, float b, float t)
{
	if(t > b) return b;
	if(t < a) return a;
	return t;
}

sf::Vector2f closestPointToLine(sf::Vector2f A, sf::Vector2f B, sf::Vector2f P)
{
	sf::Vector2f A_to_P = P - A;
	sf::Vector2f A_to_B = B - A;

	float from_A_to_proj = dot(A_to_B, A_to_P) / length_squared(A_to_B);

	return A + A_to_B * clamp(0,1,from_A_to_proj);
}

sf::Vector2f norm(const sf::Vector2f a)
{
	return a / length(a);
}