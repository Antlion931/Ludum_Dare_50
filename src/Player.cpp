#include <SFML/Graphics.hpp>
#include <cmath>

#include "Player.hpp"

void Player::onUpdate(const sf::Time &delta)
{
    if(false) //TODO: add cheching visible;
    {
        return;
    }
    velocity = {0,0};

    if(currentState == DYING)
    {
        currentTime += delta.asSeconds();

        if(currentTime > dyingTime)
        {
            currentTime = 0.0f;
            currentState = DEAD;
        }
    }
    else if(currentState == PUNCH)
    {
        currentTime += delta.asSeconds();

        if(currentTime > punchTime)
        {
            currentTime = 0.0f;
            currentState = IDLE;
        }
    }
    else if(currentState != DEAD)
    {
        currentState = IDLE;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocity.x -= speed;
            isFaceingRight = false;
            currentState = RUN;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            velocity.x += speed;
            currentState = RUN;

            isFaceingRight = true;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            velocity.y -= speed;
            currentState = RUN;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            velocity.y += speed;
            currentState = RUN;

        }

        if(std::abs(velocity.x) > 0.0f && std::abs(velocity.y > 0.0f))
        {
            velocity.x /= std::sqrt(2);
            velocity.y /= std::sqrt(2);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            currentState = PUNCH;
        }
    }

    translate({velocity.x * delta.asSeconds() , velocity.y * delta.asSeconds()});
    setCorrectAnimation();

    currentAnimation->update(delta, isFaceingRight);

    body.setTexture(currentAnimation -> getTexture());
    body.setTextureRect(currentAnimation->getIntRect());
}

Player::Player(sf::Vector2f position, sf::Vector2f size, float _speed, float _punchTime, float _dyingTime) : 
Character(position, size, _speed), punchTime(_punchTime), dyingTime(_dyingTime)
{
    currentTime = 0.0f;
}