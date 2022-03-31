#pragma once

#include <SFML/Graphics.hpp>

#include "Progressbar.hpp"
#include "stuff.hpp"

class MouseChangeableProgressbar : public Progressbar
{
public:
    MouseChangeableProgressbar(float width, float height, sf::Color backgroundColor, sf::Color fillColor);

    void update(sf::RenderWindow& window);
};