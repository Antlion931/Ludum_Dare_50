#pragma once
#include <SFML/Graphics.hpp>

#include "Character.hpp"

class Player : public Character
{
public:
    Player(sf::Vector2f position, sf::Vector2f size, float _speed, float _punchTime, float _dyingTime);

protected:
    float currentTime;
    float punchTime;
    float dyingTime;

   //void onDraw(sf::RenderTarget &target) const override;
    void onUpdate(const sf::Time &delta) override;
    //void onResize(Resolution resolution) override;
};
