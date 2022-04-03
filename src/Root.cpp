#include "Root.hpp"

void Root::setLevel(int level)
{
    gui->setLevel(level);
    game->setLevel(level);
}

void Root::setGUI(std::shared_ptr<LevelLoader> _gui)
{
    addChild(_gui);
    gui = _gui;
}

void Root::setGame(std::shared_ptr<LevelLoader> _game)
{
    addChild(_game);
    game = _game;
}