#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

#include "AnimationManager.hpp"
#include "TextureLoaderPrototypeFactory.hpp"

AnimationManager::AnimationManager(std::string animationDirectoryName, std::map<std::string, float> times, std::string _defaultAnimation) 
: defaultAnimation(_defaultAnimation)
{
    TextureLoaderPrototypeFactory *factory = TextureLoaderPrototypeFactory::getInstance();
    loader = factory->make(animationDirectoryName);

    for(std::map<std::string, float>::iterator t = times.begin(); t != times.end(); ++t)
    {
        addAnimation(t->first, t->second);
    }

    changeAndReset(defaultAnimation);

    intRect.height = loader->returnTexture(fileName(currentAnimation, currentIndex))->getSize().y;
    intRect.width = loader->returnTexture(fileName(currentAnimation, currentIndex))->getSize().x;
}

void AnimationManager::addAnimation(std::string name, float time)
{
    int amount = 0;
    while(loader->checkIfThereIs(fileName(name, amount)))
        amount++;
    
    assert(amount > 0);
    speeds[name] =  time / amount;
    amounts[name] = amount;
}

std::string AnimationManager::fileName(std::string animation, int index)
{
    return animation + '_' + std::to_string(index);
}

void AnimationManager::changeAndReset(std::string animation, bool isPlayOnce)
{
    currentAnimation = animation;
    currentIndex = 0;
    currentTime = 0.0f;
    animationPlayOnce = isPlayOnce;
}

void AnimationManager::setDefault(std::string animtion)
{
    defaultAnimation = animtion;
}

std::shared_ptr<sf::Texture> AnimationManager::getTexture()
{
    return loader->returnTexture(fileName(currentAnimation, currentIndex));
    return nullptr;
}

sf::IntRect AnimationManager::getIntRect()
{
    return intRect;
}

void AnimationManager::play(std::string animation)
{
    if(!animationPlayOnce && animation != currentAnimation)
        changeAndReset(animation);
}
    
void AnimationManager::playOnce(std::string animation)
{
    if(animation != currentAnimation)
        changeAndReset(animation, true);
}

void AnimationManager::update(const sf::Time& delta, bool isFacedRight)
{
    currentTime += delta.asSeconds();

    if(currentTime > speeds[currentAnimation])
    {
        currentTime -= speeds[currentAnimation];
        currentIndex++;
        if(currentIndex >= amounts[currentAnimation])
        {
            if(animationPlayOnce)
                changeAndReset(defaultAnimation);
            else
                currentIndex = 0;
        }
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
