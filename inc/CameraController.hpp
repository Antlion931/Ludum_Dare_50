#pragma once
#include "Player.hpp"

class CameraController : public Node
{
private:
    std::shared_ptr<Player> player;
    sf::View view;

public:
    CameraController(std::shared_ptr<Player> _player);

    sf::View getView();

protected:
    void onUpdate(const sf::Time& delta) override;
};