#include <SFML/Graphics.hpp>

#include "MouseChangeableProgressbar.hpp"
#include "Progressbar.hpp"

MouseChangeableProgressbar::MouseChangeableProgressbar(float width, float height, sf::Color backgroundColor, sf::Color fillColor)
: Progressbar(width, height, backgroundColor, fillColor)
{}

void MouseChangeableProgressbar::update(sf::RenderWindow& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f bodySize = getSize();
        sf::Vector2f bodyPosition = getPosition();

        bool IsMouseBetweenPositionX = (mousePosition.x >= bodyPosition.x) && (mousePosition.x <= bodyPosition.x + bodySize.x);
        bool isMouseBetweenPositionY = (mousePosition.y >= bodyPosition.y) && (mousePosition.y <= bodyPosition.y + bodySize.y);

        if( IsMouseBetweenPositionX && isMouseBetweenPositionY)
        {
            float newProgress = (mousePosition.x - bodyPosition.x) / bodySize.x;
            setProgress(newProgress);
        }
    }
}