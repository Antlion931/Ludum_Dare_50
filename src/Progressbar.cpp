#include <SFML/Graphics.hpp>

#include "Progressbar.hpp"

Progressbar::Progressbar(float width, float height, sf::Color backgroundColor, sf::Color fillColor)
{
    background.setFillColor(backgroundColor);
    bar.setFillColor(fillColor);

    sf::Vector2f backgroundSize(width, height);
    sf::Vector2f barSize(0.0f, height);

    background.setSize(backgroundSize);
    bar.setSize(barSize);

    background.setPosition(0.0f, 0.0f);
    bar.setPosition(0.0f, 0.0f);
}

float Progressbar::getProgress()
{
    float progress = bar.getSize().x / background.getSize().x;
    return progress;
}

void Progressbar::changeProgress(float change)
{
    float newProgress = getProgress() + change;
    setProgress(newProgress);
}

void Progressbar::setProgress(float newProgress)
{
    if(newProgress > 1.0f)
    {
        newProgress = 1.0f;
    }
    else if(newProgress < 0.0f)
    {
        newProgress = 0.0f;
    }

    sf::Vector2f newBarSize(background.getSize().x * newProgress, background.getSize().y); 
    bar.setSize(newBarSize);
}

void Progressbar::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
    target.draw(background, transform);
    target.draw(bar, transform);
}

void Progressbar::onResize(Resolution resolution)
{
    background.setScale(resolution.getVector2fScale());
    bar.setScale(resolution.getVector2fScale());
}

void Progressbar::setPosition(sf::Vector2f positon)
{
    m_transform.translate(positon);
}

sf::Vector2f Progressbar::getPosition()
{
    return background.getPosition();
}

sf::Vector2f Progressbar::getSize()
{
    return background.getSize();
}

void Progressbar::setSize(float width, float height)
{
    sf::Vector2f backgroundSize(width, height);
    sf::Vector2f barSize(width * getProgress(), height);

    background.setSize(backgroundSize);
    bar.setSize(barSize);
}
