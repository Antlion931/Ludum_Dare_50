#pragma once
#include "Button.h"

class TextButton : public Button
{
private:
	sf::Text text;

public:
	TextButton(sf::Vector2f position, sf::Vector2f size,
		sf::Text _text);

	void setText(std::string _text);
	void setFont(sf::Font font);

protected:
	void onPressed() override;
	void onEntered() override;
	void onCancelled() override;
	void onReleased() override;

	void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const override;

private:
	//void resize();
	void adjustText();
	// offset + wielkosc liter
};

