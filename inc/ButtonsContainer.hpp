#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

#include "Container.hpp"
#include "ColoredButton.hpp"


class ButtonsContainer : public Container
{
public:
    ButtonsContainer(sf::Font _font);
    void makeColoredButton(std::string text, int characterSize, sf::Vector2f position, sf::Vector2f size);
    std::shared_ptr<ColoredButton> get(std::string text);

private:
    std::map<std::string, std::shared_ptr<ColoredButton>> buttons;
    sf::Font font;
};