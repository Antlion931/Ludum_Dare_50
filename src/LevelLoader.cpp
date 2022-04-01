#include "LevelLoader.hpp"

void LevelLoader::setLevel(int level)
{
	currentLevel = level;
}
void LevelLoader::update(const sf::Time& delta)
{
	levels[currentLevel]->update(delta);
	
}
void LevelLoader::addLevel(std::shared_ptr<Node> level)
{
	levels.push_back(level);
	addChild(level);
}
void LevelLoader::draw(sf::RenderTarget& target)
{
	levels[currentLevel]->draw(target);
}
