#pragma once
#include "Node.hpp"
#include "LevelLoader.hpp"
#include "SFML/Graphics.hpp"
#include "Music.hpp"
#include <memory>

class Root : public Node
{
private:
    std::shared_ptr<LevelLoader> game;
    std::shared_ptr<LevelLoader> gui;
    Music& GLOBAL_MUSIC;

public:
    Root(Music& _GLOBAL_MUSIC);
    void setLevel(int level);
    void setGUI(std::shared_ptr<LevelLoader> _gui);
    void setGame(std::shared_ptr<LevelLoader> _game);
};
