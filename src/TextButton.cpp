#include "TextButton.hpp"



#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))


TextButton::TextButton(sf::Vector2f position, sf::Vector2f size,
	sf::Text _text) : Button(position, size), text(_text), 
	onPressedFontStyle(sf::Color::Yellow, sf::Color::Black, 4), onReleasedFontStyle(sf::Color::Red, sf::Color::Black, 0.0),
	onEnteredFontStyle(sf::Color::Yellow, sf::Color::Black, 4), onNotHoveredFontStyle(sf::Color::Yellow, sf::Color::Black, 4)
{
	adjustText();

}

void TextButton::setText(std::string _text)
{
	text.setString(_text);
	adjustText();
}

void TextButton::setFont(sf::Font font)
{
	text.setFont(font);
	adjustText();
}

void TextButton::adjustText()
{
	// wielkosc liter
	text.setCharacterSize(min(text.getCharacterSize(), box.getSize().y));

	// wysrodkowac tekst
	sf::FloatRect textRect = text.getLocalBounds();
	float x = (box.getSize().x / 2) - textRect.width / 2;
	float y = (box.getSize().y / 2) - textRect.height;
	text.setPosition(x,y);
}

void TextButton::onDraw(sf::RenderTarget& target)
{
	target.draw(box, m_global_transform.getTransform());
	target.draw(text, m_global_transform.getTransform());
}

void TextButton::onResize(Resolution resolution)
{
}

void TextButton::onPressed()
{
	text.setFillColor(onPressedFontStyle.fillColor);
	text.setOutlineColor(onPressedFontStyle.outlineColor);
	text.setOutlineThickness(onPressedFontStyle.outlineThickness);
	
}	
void TextButton::onEntered()
{
	text.setFillColor(onEnteredFontStyle.fillColor);
	text.setOutlineColor(onEnteredFontStyle.outlineColor);
	text.setOutlineThickness(onEnteredFontStyle.outlineThickness);
}
void TextButton::onNotHovered()
{
	text.setFillColor(onNotHoveredFontStyle.fillColor);
	text.setOutlineColor(onNotHoveredFontStyle.outlineColor);
	text.setOutlineThickness(onNotHoveredFontStyle.outlineThickness);
}
void TextButton::onReleased()
{
	text.setFillColor(onReleasedFontStyle.fillColor);
	text.setOutlineColor(onReleasedFontStyle.outlineColor);
	text.setOutlineThickness(onReleasedFontStyle.outlineThickness);
}


void TextButton::setOnPressedFontStyle(Style style)
{
	onPressedFontStyle = style;
}
void TextButton::setOnEnteredFontStyle(Style style)
{
	onEnteredFontStyle = style;
}
	
void TextButton::setOnNotHoveredFontStyle(Style style)
{
	onNotHoveredFontStyle = style;
}
void TextButton::setOnReleasedFontStyle(Style style)
{
	onReleasedFontStyle = style;
}


