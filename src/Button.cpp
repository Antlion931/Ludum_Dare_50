#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Toolkit.hpp"


Button::Button(sf::Vector2f position, sf::Vector2f size) : buttonState(State::NOT_HOVERED)
{
	m_local_transform.setPosition(position);
	box.setSize(size);
}

void Button::setSoundSystem(SoundSystem* _soundSystem)
{
	soundSystem = _soundSystem;
}

bool Button::isPressed(sf::RenderWindow& window)
{
	if (!active)
		return 0;
	if (clamp(box, m_global_transform.getTransform().getInverse().transformPoint(window.mapPixelToCoords(sf::Mouse::getPosition(window)))))
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
		else if(buttonState != State::HOVERED)
		{
			onEntered();
			soundSystem->playSound("buttonSound.wav");

			buttonState = State::HOVERED;
		}
	}
	else
	{
		buttonState = State::NOT_HOVERED;
		onNotHovered();
	}
	
	return false;
}

void Button::onDraw(sf::RenderTarget& target)
{
	target.draw(box,m_global_transform.getTransform());
}

void Button::onResize(Resolution resolution) {
	box.setScale(resolution.getVector2fScale());
}
