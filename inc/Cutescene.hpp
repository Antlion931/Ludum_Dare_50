#include "Button.hpp"
#include "TextureLoader.hpp"

class Cutescene : public Button
{
public:
    Cutescene(sf::Vector2f position, sf::Vector2f size, sf::Texture* _texture1, sf::Texture* _texture2, sf::Texture* _texture3);
    bool isCutesceneEnded();

protected:
    sf::Texture* texture1;
    sf::Texture* texture2;
    sf::Texture* texture3; 
    float currentTime;
	virtual void onUpdate(const sf::Time& delta) override;
};
