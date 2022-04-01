#include "Button.hpp"
#include "Toolkit.hpp"


Button::Button(sf::Vector2f position, sf::Vector2f size) : buttonState(State::NOT_HOVERED)
{
	m_transform.translate(position);
	box.setSize(size);
}

bool Button::isPressed(sf::RenderWindow& window)
{
	if (clamp(box, m_combined_transform.getInverse().transformPoint(sf::Vector2f(sf::Mouse::getPosition(window)))))
	{
		
		
		onEntered();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			onPressed();
			buttonState = State::PRESSED;
		}
		else if (buttonState == State::PRESSED)
		{
			onReleased();
			return true;
		}
		else
		{
			buttonState = State::HOVERED;
		}
	}
	else
	{
		buttonState = State::NOT_HOVERED;
		onCancelled();
	}
	
	return false;
}

void Button::onResize(Resolution resolution)
{
	box.setScale(resolution.getVector2fScale());
}

void Button::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(box,transform);
}
