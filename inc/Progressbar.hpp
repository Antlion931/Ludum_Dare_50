#pragma once

#include <SFML/Graphics.hpp>

#include "Resolution.hpp"
#include "Node.hpp"

class Progressbar : public Node
{
public:
    Progressbar(float width, float height, sf::Color backgroundColor, sf::Color fillColor);
    
    float getProgress();
    void setProgress(float newProgress);
    void changeProgress(float change);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void setSize(float width, float height);
    void setPosition(sf::Vector2f position);

protected:
    virtual void onDraw(sf::RenderTarget& target);
    virtual void onResize(Resolution resolution);
    sf::RectangleShape bar;
    sf::RectangleShape background;
};
