#include <SFML/Graphics.hpp>
#include <cmath>

#include "Player.hpp"

void Player::onUpdate(const sf::Time &delta)
{
    if(false) //TODO: add cheching visible;
    {
        return;
    }

    sf::Vector2f signs(1,1);
    velocity = {0,0};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x = speed;
        signs.x = -1;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x = speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity.y = speed;
        signs.y = -1;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y = speed;
    }

    if(velocity.x > 0.0f && velocity.y > 0.0f)
    {
        velocity.x /= std::sqrt(2);
        velocity.y /= std::sqrt(2);
    }

    velocity.x *= signs.x;
    velocity.y *= signs.y;

    translate({velocity.x * delta.asSeconds() , velocity.y * delta.asSeconds()});
    std::cout << velocity.x * delta.asSeconds() << " " << velocity.y * delta.asSeconds() << std::endl;
}

Player::Player(sf::Vector2f position, float radius, float _speed) : Character(position, radius, _speed)
{}