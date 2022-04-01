#pragma once
#include <SFML/Graphics.hpp>

class Resolution
{
public:
    enum resolution
    {
        _1336x768 = 1336,
        _1600x900 = 1600,
        _1280x720 = 1280,
        _1920x1080 = 1920
    };
    Resolution(resolution defaultResolution);
    void changeResolution(resolution newResolution, sf::RenderWindow& window);
    float getScale();
    sf::Vector2f getVector2fScale();
    sf::VideoMode getDefault();

private:
    sf::Vector2u getSize();
    sf::View getView();
    resolution defaultResolution;
    resolution currentResolution;
};
