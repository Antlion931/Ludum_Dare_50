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
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void setSize(float width, float height);
    virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;
    virtual void onResize(Resolution resolution);

protected:
    sf::RectangleShape bar;
    sf::RectangleShape background;
};
