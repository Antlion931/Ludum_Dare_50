#include <SFML/Graphics.hpp>
#include "ColoredButton.hpp"

ColoredButton::ColoredButton(sf::Vector2f position, sf::Vector2f size, sf::Text _text) : TextButton(position, size, _text),
 onPressedButtonStyle(sf::Color(190, 190, 190), sf::Color(170, 170, 170), 10), onEnteredButtonStyle(sf::Color(210, 210, 210), sf::Color(190, 190, 190), 30),
 onNotHoveredButtonStyle(sf::Color(200, 200, 200), sf::Color(180, 180, 180), 20), onReleasedButtonStyle(sf::Color::Green, sf::Color::Black, 0.0)
{


}

void ColoredButton::setOnPressedButtonStyle(Style style)
{
    onPressedButtonStyle = style;
}
void ColoredButton::setOnEntredButtonStyle(Style style)
{
    onEnteredButtonStyle = style;
}
void ColoredButton::setOnNotHoveredButtonStyle(Style style)
{
    onNotHoveredButtonStyle = style;
}
void ColoredButton::setOnReleasedButtonStyle(Style style)
{
    onReleasedButtonStyle = style;
}


void ColoredButton::onPressed()
{
	text.setFillColor(onPressedFontStyle.fillColor);
	text.setOutlineColor(onPressedFontStyle.outlineColor);
	text.setOutlineThickness(onPressedFontStyle.outlineThickness);

    box.setFillColor(onPressedButtonStyle.fillColor);
	box.setOutlineColor(onPressedButtonStyle.outlineColor);
	box.setOutlineThickness(onPressedButtonStyle.outlineThickness);

	
}	
void ColoredButton::onEntered()
{
	text.setFillColor(onEnteredFontStyle.fillColor);
	text.setOutlineColor(onEnteredFontStyle.outlineColor);
	text.setOutlineThickness(onEnteredFontStyle.outlineThickness);

    box.setFillColor(onEnteredButtonStyle.fillColor);
	box.setOutlineColor(onEnteredButtonStyle.outlineColor);
	box.setOutlineThickness(onEnteredButtonStyle.outlineThickness);
}
void ColoredButton::onNotHovered()
{
	text.setFillColor(onNotHoveredFontStyle.fillColor);
	text.setOutlineColor(onNotHoveredFontStyle.outlineColor);
	text.setOutlineThickness(onNotHoveredFontStyle.outlineThickness);

    box.setFillColor(onNotHoveredButtonStyle.fillColor);
	box.setOutlineColor(onNotHoveredButtonStyle.outlineColor);
	box.setOutlineThickness(onNotHoveredButtonStyle.outlineThickness);
}
void ColoredButton::onReleased()
{
    text.setFillColor(onReleasedFontStyle.fillColor);
	text.setOutlineColor(onReleasedFontStyle.outlineColor);
	text.setOutlineThickness(onReleasedFontStyle.outlineThickness);

	box.setFillColor(onReleasedButtonStyle.fillColor);
	box.setOutlineColor(onReleasedButtonStyle.outlineColor);
	box.setOutlineThickness(onReleasedButtonStyle.outlineThickness);
}


