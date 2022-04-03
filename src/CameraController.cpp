#include "CameraController.hpp"


CameraController::CameraController(std::shared_ptr<Node> _followed)
{
    followed = _followed;
}


sf::Vector2f CameraController::getRequiredTranslation()
{
    return required_translation;
}


void CameraController::onUpdate(const sf::Time& delta)
{
    required_translation = followed->getGlobalTransform().getPosition();
}

