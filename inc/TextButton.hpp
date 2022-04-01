#pragma once
#include "Button.hpp"
#include "Resolution.hpp"
#include "Style.hpp"


class TextButton : public Button
{
private:
	

public:
	TextButton(sf::Vector2f position, sf::Vector2f size,
		sf::Text _text);

	void setText(std::string _text);
	void setFont(sf::Font font);

	void setOnPressedFontStyle(Style style);
	void setOnEnteredFontStyle(Style style);
	void setOnNotHoveredFontStyle(Style style);
	void setOnReleasedFontStyle(Style style);






protected:
	void onPressed() override;
	void onEntered() override;
	void onNotHovered() override;
	void onReleased() override;

	void onDraw(sf::RenderTarget& target) const override;
	void onResize(Resolution resolution) override;

	Style onPressedFontStyle;
	Style onEnteredFontStyle;
	Style onNotHoveredFontStyle;
	Style onReleasedFontStyle;
	
	sf::Text text;
	


private:
	//void resize();
	void adjustText();
	// offset + wielkosc liter
};
