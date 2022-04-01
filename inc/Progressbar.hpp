#pragma once

#include <SFML/Graphics.hpp>

#include "Resolution.hpp"
#include "stuff.hpp"

class Progressbar : public stuff
{
public:
    Progressbar(float width, float height, sf::Color backgroundColor, sf::Color fillColor);
    
    float getProgress();
    void setProgress(float newProgress);
    void changeProgress(float change);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void setSize(float width, float height);
    void draw(sf::RenderWindow& window);
    void resize(Resolution resolution);

protected:
    sf::RectangleShape bar;
    sf::RectangleShape background;
};