#include <SFML/Graphics.hpp>

#include <iostream>
#include "Animation.hpp"

Animation::Animation(std::string directoryPath, float _animationSpeed) : loader(directoryPath), animationSpeed(_animationSpeed)
{
    currentIndex = 0;
    currentTime = 0;
    intRect.height = loader.returnTexture(0)->getSize().y;
    intRect.width = loader.returnTexture(0)->getSize().x;
}

sf::Texture* Animation::getTexture()
{
    return loader.returnTexture(currentIndex);
}

void Animation::update(const sf::Time& delta, bool isFacedRight)
{
    currentTime += delta.asSeconds();
    intRect.top = 0;

    if(currentTime > animationSpeed)
    {
        currentIndex++;
        if(currentIndex >= loader.getAmountOfTestures())
        {
            currentIndex = 0;
        } 
        currentTime -= animationSpeed;
    }

    if(isFacedRight)
    {
        intRect.width = abs(intRect.width);
        intRect.left = 0;
    }
    else
    {
        intRect.width = -abs(intRect.width);
        intRect.left = -intRect.width;
    }
}

void Animation::reset()
{
    currentIndex = 0;
    currentTime = 0.0;
}

sf::IntRect Animation::getIntRect()
{
    return intRect;
}
