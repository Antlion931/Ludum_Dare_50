#include <SFML/Graphics.hpp>
#include <assert.h>

#include <iostream>
#include "Animation.hpp"

Animation::Animation(std::string directoryPath, std::vector<float> _speeds, std::vector<int> _animationIndex) 
: loader(directoryPath), speeds(_speeds), animationIndex(_animationIndex)
{
    assert(speeds.size() == 5);
    assert(animationIndex.size() == 5);

    currentAnimation = IDLE;
    currentIndex = 1;
    currentTime = 0.0f;
    intRect.height = loader.returnTexture("1.png")->getSize().y;
    intRect.width = loader.returnTexture("1.png")->getSize().x;

    fileFormat = ".png";
}

std::shared_ptr<sf::Texture> Animation::getTexture()
{
    return loader.returnTexture(std::to_string(currentIndex) + fileFormat);
    return nullptr;
}

void Animation::update(const sf::Time& delta, bool isFacedRight)
{
    currentTime += delta.asSeconds();
    intRect.top = 0;

    if(currentTime > speeds[currentAnimation])
    {
        currentIndex++;
        if(currentIndex >= animationIndex[currentAnimation])
        {
            if(currentAnimation == IDLE)
            {
                currentIndex = 1;
            }
            else
            {
                currentIndex = animationIndex[currentAnimation - 1];
            }
        } 
        currentTime -= speeds[currentAnimation];
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
    if(currentAnimation == IDLE)
    {
        currentIndex = 1;
    }
    else
    {
        currentIndex = animationIndex[currentAnimation - 1];
    }
    currentTime = 0.0f;
}

sf::IntRect Animation::getIntRect()
{
    return intRect;
}

void Animation::changeAnimation(AnimationType newAnimationType)
{
    if(currentAnimation != newAnimationType)
    {
        currentAnimation = newAnimationType;
        reset();
    }
}

AnimationType Animation::getCurrentAnimation()
{
    return currentAnimation;
}
