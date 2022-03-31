#pragma once
#include <SFML/Graphics.hpp>

#include "Resolution.hpp"

class stuff
{
public:
    stuff()
    {
        resolution = nullptr;
    }
    Resolution* resolution;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void resize(sf::RenderWindow &window) = 0;
};
