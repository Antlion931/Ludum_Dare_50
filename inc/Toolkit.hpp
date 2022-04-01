#pragma once
#include <SFML/Graphics.hpp>

// check whether b is in bounds of a
bool clamp(sf::RectangleShape a, sf::Vector2f b);

bool clamp(sf::RectangleShape a, sf::Vector2i b);
