#pragma once
#include <vector>
#include <memory>
#include "Node.hpp"

class LevelLoader : public Node
{
	std::shared_ptr<Node> null_node = std::make_shared<Node>(Node());

private:
	std::vector<std::shared_ptr<Node>> levels;
	int currentLevel = 0;
public:
	LevelLoader(int size);
	void setLevel(int level);
	void addLevel(int id, std::shared_ptr<Node> level);
	void update(const sf::Time& delta);
	void draw(sf::RenderTarget& target);
};

