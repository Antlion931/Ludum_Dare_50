#pragma once
#include <vector>
#include <memory>

#include "Container.hpp"
class LevelLoader : public Node
{
private:
	std::vector<std::shared_ptr<Node>> levels;
	int currentLevel = 0;
public:
	void setLevel(int level);
	void addLevel(std::shared_ptr<Node> level);
	void update(const sf::Time& delta);
	void draw(sf::RenderTarget& target);
};

