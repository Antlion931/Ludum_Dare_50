#include <SFML/Graphics.hpp>


#include <iostream>
#include "Animation.hpp"

Animation::Animation(std::string directoryPath, float _animationSpeed) : loader(directoryPath), animationSpeed(_animationSpeed)
{
    currentIndex = "1.png";
    currentTime = 0;
    intRect.height = loader.returnTexture("1.png")->getSize().y;
    intRect.width = loader.returnTexture("1.png")->getSize().x;
}

std::shared_ptr<sf::Texture> Animation::getTexture()
{
    return loader.returnTexture(currentIndex);
    return nullptr;
}

void Animation::update(const sf::Time& delta, bool isFacedRight)
{
    currentTime += delta.asSeconds();
    intRect.top = 0;

    if(currentTime > animationSpeed)
    {
        currentIndex = std::to_string(std::stoi(currentIndex)+1).append(".png");
        if(std::stoi(currentIndex) >= loader.getAmountOfTextures())
        {
            currentIndex = "1.png";
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
    currentIndex = "1.png";
    currentTime = 0.0;
}

sf::IntRect Animation::getIntRect()
{
    return intRect;
}
