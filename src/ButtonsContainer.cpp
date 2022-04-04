#include <SFML/Graphics.hpp>

#include "ButtonsContainer.hpp"

void ButtonsContainer::makeColoredButton(std::string text, int characterSize, sf::Vector2f position, sf::Vector2f size)
{
    sf::Text t(text, font, characterSize);
    buttons[text] = std::make_shared<ColoredButton>(ColoredButton(position, size, t));
    buttons[text]->setName(text);
    buttons[text]->setSoundSystem(soundSystem);
    addChild(buttons[text]);
}

ButtonsContainer::ButtonsContainer(sf::Font _font, SoundSystem* _soundSystem) : font(_font), soundSystem(_soundSystem)
{}

std::shared_ptr<ColoredButton> ButtonsContainer::get(std::string text)
{
    return buttons[text];
}
