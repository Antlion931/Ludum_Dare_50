#include "Button.hpp"

class Cutescene : public Button
{
public:
    Cutescene(sf::Vector2f position, sf::Vector2f size);

protected:
	virtual void onUpdate(const sf::Time& delta) override;
};
