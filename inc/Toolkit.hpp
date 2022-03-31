#pragma once
#include <SFML/Graphics.hpp>


// check whether b is in bounds of a
bool clamp(sf::RectangleShape a, sf::Vector2f b)
{
	sf::Vector2f size = a.getSize();
	sf::Vector2f position = a.getPosition();

	return b.x <= position.x + size.x &&
		   b.x >= position.x &&
		   b.y <= position.y + size.y &&
		   b.y >= position.y;
}


bool clamp(sf::RectangleShape a, sf::Vector2i b)
{
	sf::Vector2f size = a.getSize();
	sf::Vector2f position = a.getPosition();

	return b.x <= position.x + size.x &&
		b.x >= position.x &&
		b.y <= position.y + size.y &&
		b.y >= position.y;
}