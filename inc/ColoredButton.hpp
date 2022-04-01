#pragma once
#include <SFML/Graphics.hpp>
#include "TextButton.hpp"


class ColoredButton : public TextButton
{
    public:
        ColoredButton(sf::Vector2f position, sf::Vector2f size, sf::Text _text);

        void setOnPressedButtonStyle(Style style);
        void setOnEntredButtonStyle(Style style);
        void setOnNotHoveredButtonStyle(Style style);
        void setOnReleasedButtonStyle(Style style);

    protected:
        void onPressed() override;
	    void onEntered() override;
	    void onNotHovered() override;
	    void onReleased() override;

        Style onPressedButtonStyle;
	    Style onEnteredButtonStyle;
	    Style onNotHoveredButtonStyle;
	    Style onReleasedButtonStyle;
};