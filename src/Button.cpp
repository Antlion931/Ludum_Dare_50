#include "Button.hpp"
#include "Toolkit.hpp"


Button::Button(sf::Vector2f position, sf::Vector2f size) : buttonState(State::NOT_HOVERED)
{
	m_local_transform.setPosition(position);
	box.setSize(size);
}


bool Button::isPressed(sf::RenderWindow& window)
{
	if (clamp(box, m_global_transform.getTransform().getInverse().transformPoint(sf::Vector2f(sf::Mouse::getPosition(window)))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			onPressed();
			buttonState = State::PRESSED;
		}
		else if (buttonState == State::PRESSED)
		{
			onReleased();
			buttonState = State::HOVERED;
			return true;
		}
		else
		{
			onEntered();
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

void Button::onDraw(sf::RenderTarget& target) const
{
	target.draw(box,m_global_transform.getTransform());
}
