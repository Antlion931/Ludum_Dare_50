#pragma once
#include <SFML/Graphics.hpp>

#include "Character.hpp"
#include "SoundSystem.hpp"
#include "MovingCircle.hpp"

class Player : public Character
{
public:
    Player(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, float _punchTime, float _dyingTime);

protected:
    float currentTime;
    float punchTime;
    float dyingTime;

    std::shared_ptr<MovingCircle> snipersRedDot;
    sf::Vector2f headPosition;

    void onDraw(sf::RenderTarget &target) const override;
    void onUpdate(const sf::Time &delta) override;
    //void onResize(Resolution resolution) override;
};
