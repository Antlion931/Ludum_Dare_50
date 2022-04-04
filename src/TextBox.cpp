#include <SFML/Graphics.hpp>

#include "TextBox.hpp"


TextBox::TextBox(sf::Vector2f positon, sf::Vector2f size, sf::Text _text) : TextButton(positon, size, _text)
{
    box.setFillColor(sf::Color(0,0,0,0));
    onNotHovered();
}

void TextBox::setString(std::string newTextString)
{
    text.setString(newTextString);
}

