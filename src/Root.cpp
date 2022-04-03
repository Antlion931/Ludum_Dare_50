#include "Root.hpp"
#include "Toolkit.hpp"

void Root::setLevel(int level)
{
    gui->setLevel(level);
    game->setLevel(level);

    switch (level)
    {
    case GAME:
    case TEST_PLAY:
        GLOBAL_MUSIC.stopMusic();
        GLOBAL_MUSIC.setTrack("GamePlayMusic.wav");    
    break;
    
    case SETTINGS:
        GLOBAL_MUSIC.stopMusic();    
    break;

    case MAIN_MENU:
        GLOBAL_MUSIC.stopMusic();  
    break;
    }
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

Root::Root(Music& _GLOBAL_MUSIC) : GLOBAL_MUSIC(_GLOBAL_MUSIC)
{}
