#pragma once
#include <SFML/Graphics.hpp>

#include "Character.hpp"
#include "SoundSystem.hpp"
#include "MovingCircle.hpp"

class Player : public Character
{
public:
    Player(SoundSystem& soundSystem, sf::Vector2f position, sf::Vector2f size, float _speed, Animation _animation, float _dyingTime, float _punchTime);
    Player(SoundSystem& soundSystem);

protected:
    float punchTime;

    std::string punchSoundDirectory; 

    std::shared_ptr<MovingCircle> snipersRedDot;
    sf::Vector2f headPosition;

    void onDraw(sf::RenderTarget &target) override;
    void onUpdate(const sf::Time &delta) override;
    //void onResize(Resolution resolution) override;

private:
    void randHeadPositon();
    void updateSinpersRedDot(const sf::Time& delta);
    void updateVelocty(const sf::Time& delta);
};
