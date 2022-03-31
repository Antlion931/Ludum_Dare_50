#pragma once
#include "Node.hpp"
#include <string>


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

	virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const;

protected:
	sf::RectangleShape box;

	virtual void onPressed() {};
	virtual void onEntered() {};
	virtual void onCancelled() {};
	virtual void onReleased() {};
};

