#include <SFML/Graphics.hpp>

class stuff
{
public:
    virtual void draw(sf::RenderWindow &window);
    virtual void resize(sf::RenderWindow &window);
};