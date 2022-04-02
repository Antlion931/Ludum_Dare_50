#pragma once
#include "Node.hpp"
#include <string>
#include "Resolution.hpp"
#include <functional>

class Button : public Node
{
private:
	enum class State
	{
		NOT_HOVERED,
		HOVERED,
		PRESSED
	};

	State buttonState;

public:
	Button(sf::Vector2f position, sf::Vector2f size);
	
	bool isPressed(sf::RenderWindow& window);

	virtual void onDraw(sf::RenderTarget& target) override;
	//virtual void onUpdate();
	virtual void onResize(Resolution resolution) override;

protected:
	sf::RectangleShape box;

	virtual void onPressed() {};
	virtual void onEntered() {};
	virtual void onNotHovered() {};
	virtual void onReleased() {};
};
