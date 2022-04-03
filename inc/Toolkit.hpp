#pragma once
#include <string>
#include <SFML/Graphics.hpp>

enum LEVEL
{
MAIN_MENU,
TEST_PLAY,
SETTINGS,
GAME
};


float dot(const sf::Vector2f a, const sf::Vector2f b);

sf::Vector2f norm(const sf::Vector2f a);

float length(const sf::Vector2f a);

float length_squared(const sf::Vector2f a);

float clamp(float a, float b, float t);

sf::Vector2f closestPointToLine(sf::Vector2f A, sf::Vector2f B, sf::Vector2f P);

sf::Transformable combineTransforms(const sf::Transformable &parent, const sf::Transformable &child);
// check whether b is in bounds of a
bool clamp(sf::RectangleShape a, sf::Vector2f b);

bool clamp(sf::RectangleShape a, sf::Vector2i b);

std::ostream& operator<< (std::ostream& out, sf::Vector2f const& vec);

