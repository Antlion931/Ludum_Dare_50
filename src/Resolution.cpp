#include <SFML/Graphics.hpp>

#include "Resolution.hpp"

Resolution::Resolution(resolution _defaultResolution) : defaultResolution(_defaultResolution), currentResolution(_defaultResolution)
{}

void Resolution::changeResolution(resolution newResolution)
{
    currentResolution = newResolution;
}

float Resolution::getScale()
{
    return float(currentResolution) / float(defaultResolution);
}

sf::Vector2f Resolution::getVector2fScale()
{
    return sf::Vector2f(getScale(), getScale());
}

sf::VideoMode Resolution::getDefault()
{
    return sf::VideoMode(defaultResolution, defaultResolution * 9 / 16);
}

sf::Vector2u Resolution::getSize()
{
    return sf::Vector2u(currentResolution, currentResolution*9/16);
}

sf::View Resolution::getView()
{
    sf::FloatRect floatRect(0, 0, currentResolution, currentResolution*9 / 16);
    return sf::View(floatRect);
}
