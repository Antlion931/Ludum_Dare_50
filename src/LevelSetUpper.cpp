#include <SFML/Graphics.hpp>

#include "LevelSetUpper.hpp"
#include "Toolkit.hpp"

LevelSetUpper::LevelSetUpper(std::shared_ptr<LevelLoader> _game, std::shared_ptr<LevelLoader> _GUI, sf::Font _font) : game(_game), GUI(_GUI), font(_font)
{}

void LevelSetUpper::setUp(std::shared_ptr<Node>& level, std::shared_ptr<Node>& levelGUI, std::shared_ptr<ButtonsContainer>& buttons, LEVEL lv)
{
    std::string prefix;
    switch (lv)
    {
    case MAIN_MENU:
        prefix = "main menu ";
    break;
    
    case TEST_PLAY:
        prefix = "test ";
    break;

    case SETTINGS:
        prefix = "settings ";
    break;

    case GAME:
        prefix = "game ";
    break;
    }

    level = std::make_shared<Node>(Node());
    level->setName(prefix + "level");
    game->addLevel(lv, level);

    levelGUI = std::make_shared<Node>(Node());
    levelGUI->setName(prefix + "level GUI");
    GUI->addLevel(lv, levelGUI);

    buttons = std::make_shared<ButtonsContainer>(ButtonsContainer(font));
    buttons->setName(prefix + "buttons");
    levelGUI->addChild(buttons);
}
