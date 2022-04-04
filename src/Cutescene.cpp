#include "Cutescene.hpp"
#include <SFML/Graphics.hpp>

Cutescene::Cutescene(sf::Vector2f position, sf::Vector2f size, sf::Texture* _texture1, sf::Texture* _texture2, sf::Texture* _texture3) : Button(position, size), currentTime(0.0)
{
    texture1 = _texture1;
    texture2 = _texture2;
    texture3 = _texture3;

    box.setTexture(texture1);
}

void Cutescene::onUpdate(const sf::Time& delta)
{
    currentTime += delta.asSeconds();

    if(box.getTexture() == texture1 && currentTime > 1.0)
    {
        box.setTexture(texture2);
    }
    else if(box.getTexture() == texture2 && currentTime > 4.5)
    {
        box.setTexture(texture3);
    }
}

bool Cutescene::isCutesceneEnded()
{
    if(currentTime > 5.0)
    {
        return true;
    }
    return false;
}
