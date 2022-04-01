#pragma once
#include <SFML/Graphics.hpp>

sf::Vector2f dot(const sf::Vector2f a, const sf::Vector2f b);

sf::Transformable combineTransforms(const sf::Transformable &parent, const sf::Transformable &child);

// check whether b is in bounds of a
bool clamp(sf::RectangleShape a, sf::Vector2f b);

bool clamp(sf::RectangleShape a, sf::Vector2i b);
