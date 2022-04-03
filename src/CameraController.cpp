#include "CameraController.hpp"


CameraController::CameraController(std::shared_ptr<Player> _player) : player(_player)
{

}


sf::View CameraController::getView()
{
    return view;
}


void CameraController::onUpdate(const sf::Time& delta)
{
    view.setCenter(player->getGlobalTransform().getPosition().x, player->getGlobalTransform().getPosition().y);
}

