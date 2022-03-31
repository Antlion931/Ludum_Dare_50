#pragma once
#include <SFML/Graphics.hpp>

class stuff
{
public:
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void resize(sf::RenderWindow &window) = 0;
};
