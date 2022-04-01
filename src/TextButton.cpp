#include "TextButton.hpp"
#include "iostream"


#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))


TextButton::TextButton(sf::Vector2f position, sf::Vector2f size,
	sf::Text _text) : Button(position, size), text(_text)
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

void TextButton::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(box, transform);
	target.draw(text, transform);
}

void TextButton::onResize(Resolution resolution)
{
	box.setScale(resolution.getVector2fScale());

	text.setScale(resolution.getVector2fScale());
}

void TextButton::onPressed()
{
	box.setFillColor(sf::Color::Blue);
}
void TextButton::onEntered()
{
	box.setFillColor(sf::Color::Green);
}
void TextButton::onCancelled()
{
	box.setFillColor(sf::Color::White);
}
void TextButton::onReleased()
{
	box.setFillColor(sf::Color::Red);
}
