#pragma once
#include <SFML/Graphics.hpp>

#include "Character.hpp"

class Player : public Character
{
public:
    Player(sf::Vector2f position, float radius, float _speed);

protected:
   //void onDraw(sf::RenderTarget &target) const override;
    void onUpdate(const sf::Time &delta) override;
    //void onResize(Resolution resolution) override;
};
