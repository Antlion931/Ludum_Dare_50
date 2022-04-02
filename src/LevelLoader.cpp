#include "LevelLoader.hpp"

void LevelLoader::setLevel(int level)
{
	levels[currentLevel]->setActive(0);
	levels[currentLevel]->setVisible(0);
	currentLevel = level;
	levels[currentLevel]->setActive(1);
	levels[currentLevel]->setVisible(1);
}
void LevelLoader::update(const sf::Time& delta)
{
	levels[currentLevel]->update(delta);
	
}
void LevelLoader::addLevel(std::shared_ptr<Node> level)
{
	addChild(level);
	level->setActive(0);
	level->setVisible(0);
	levels.push_back(level);
	
}
void LevelLoader::draw(sf::RenderTarget& target)
{
	levels[currentLevel]->draw(target);
}
