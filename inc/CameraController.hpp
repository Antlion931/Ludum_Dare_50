#pragma once
#include "Player.hpp"

class CameraController : public Node
{
private:
    std::shared_ptr<Node> followed;
    sf::Vector2f required_translation = {0, 0};

public:
    CameraController(std::shared_ptr<Node> _followed);

    sf::Vector2f getRequiredTranslation();

protected:
    void onUpdate(const sf::Time& delta) override;
};