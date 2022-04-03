#pragma once

#include "TextButton.hpp"

class TextBox : public TextButton
{ 
public:
    TextBox(sf::Vector2f positon, sf::Vector2f size, sf::Text _text);
    void setString(std::string _string);
};
