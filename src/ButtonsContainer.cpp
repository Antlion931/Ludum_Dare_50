#include <SFML/Graphics.hpp>

#include "ButtonsContainer.hpp"

void ButtonsContainer::makeColoredButton(std::string text, int characterSize, sf::Vector2f position, sf::Vector2f size)
{
    sf::Text t(text, font, characterSize);
    buttons[text] = std::make_shared<ColoredButton>(ColoredButton(position, size, t));
    buttons[text]->setName(text);
    addChild(buttons[text]);
}

ButtonsContainer::ButtonsContainer(sf::Font _font) : font(_font)
{}

std::shared_ptr<ColoredButton> ButtonsContainer::get(std::string text)
{
    return buttons[text];
}
