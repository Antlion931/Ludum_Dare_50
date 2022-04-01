
#include <SFML/Graphics.hpp>

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