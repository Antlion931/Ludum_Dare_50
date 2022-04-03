#include "Node.hpp"
#include "LevelLoader.hpp"
#include <memory>

class Root : public Node
{
private:
    std::shared_ptr<LevelLoader> game;
    std::shared_ptr<LevelLoader> gui;
public:
    void setLevel(int level);
    void setGUI(std::shared_ptr<LevelLoader> _gui);
    void setGame(std::shared_ptr<LevelLoader> _game);
};
