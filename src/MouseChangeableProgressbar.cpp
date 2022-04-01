#include <SFML/Graphics.hpp>

#include "MouseChangeableProgressbar.hpp"
#include "Progressbar.hpp"
#include "Toolkit.hpp"

MouseChangeableProgressbar::MouseChangeableProgressbar(float width, float height, sf::Color backgroundColor, sf::Color fillColor)
: Progressbar(width, height, backgroundColor, fillColor)
{}

void MouseChangeableProgressbar::update(sf::RenderWindow& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f mousePosition = getGlobalTransform().getTransform().getInverse() * sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Vector2f bodySize = getSize();
        sf::Vector2f bodyPosition = getPosition();

        if(clamp(background, mousePosition))
        {
            float newProgress = (mousePosition.x - bodyPosition.x) / (bodySize.x * background.getScale().x);
            setProgress(newProgress);
        }
    }
}
