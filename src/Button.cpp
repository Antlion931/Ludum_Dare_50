<<<<<<< HEAD
#include "Button.h"
#include "Toolkit.h"
=======
#include "Button.hpp"
#include "Toolkit.hpp"
>>>>>>> acf5311044db40575f174f9389541c634871b73c


Button::Button(sf::Vector2f position, sf::Vector2f size) : buttonState(State::NOT_HOVERED)
{
<<<<<<< HEAD
	m_transform.translate(position);
=======
	m_local_transform.setPosition(position);
>>>>>>> acf5311044db40575f174f9389541c634871b73c
	box.setSize(size);
}


bool Button::isPressed(sf::RenderWindow& window)
{
<<<<<<< HEAD
	if (clamp(box, m_combined_transform.getInverse().transformPoint(sf::Vector2f(sf::Mouse::getPosition(window)))))
=======
	if (clamp(box, m_global_transform.getTransform().getInverse().transformPoint(sf::Vector2f(sf::Mouse::getPosition(window)))))
>>>>>>> acf5311044db40575f174f9389541c634871b73c
	{
		
		buttonState = State::HOVERED;
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
	}
	else
	{
		buttonState = State::NOT_HOVERED;
		onCancelled();
	}
	
	return false;
}


<<<<<<< HEAD
void Button::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(box,transform);
=======
void Button::onDraw(sf::RenderTarget& target) const
{
	target.draw(box,m_global_transform.getTransform());
>>>>>>> acf5311044db40575f174f9389541c634871b73c
}
