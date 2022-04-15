#include "Root.hpp"
#include "Toolkit.hpp"

void Root::setLevel(int level)
{
    gui->setLevel(level);
    game->setLevel(level);

    switch (level)
    {
    case CUTSCENE:
        
    break;
    case TEST_PLAY:
        musicSystem->stopMusic();
        musicSystem->setTrack("GamePlayMusic.wav");    
    break;
    
    case SETTINGS:
        musicSystem->stopMusic();    
    break;

    case MAIN_MENU:
        musicSystem->stopMusic();  
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

Root::Root()
{
    musicSystem = MusicSystem::getInstance();
}
