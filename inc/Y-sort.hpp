#pragma once
#include "Node.hpp"
#include "memory"

class YSort : public Node 
{
    static bool YComparator (std::shared_ptr<Node> const &a, std::shared_ptr<Node> const &b)
    {
        return a->getGlobalTransform().getPosition().y
             < b->getGlobalTransform().getPosition().y;
    }

    void onDraw(sf::RenderTarget &target) override;
public:
    std::shared_ptr<std::vector<std::shared_ptr<Node>>> getChildren()
    {
        return std::make_shared<std::vector<std::shared_ptr<Node>>>(m_children);
    }
};