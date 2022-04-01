#pragma once
#include <SFML/Graphics.hpp>

#include "Resolution.hpp"

class stuff
{
public:
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void resize(Resolution resolution) = 0;
};
