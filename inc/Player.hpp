#pragma once
#include <SFML/Graphics.hpp>

#include "GameObject.hpp"
#include "SoundSystem.hpp"
#include "MovingCircle.hpp"

class Player : public GameObject
{
public:
    Player(sf::Vector2f position, sf::Vector2f size, float _speed, AnimationManager _animation, float _dyingTime, float _punchTime);
    Player();

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
