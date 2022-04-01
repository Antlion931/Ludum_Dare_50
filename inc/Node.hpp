#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Resolution.hpp"

class Node
{
public:
    void transform(const sf::Transform& parentTransform);
    void draw(sf::RenderTarget& target) const;
    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);
    void printChildren();
    void resize(Resolution resolution);

protected:

    virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const{}
    virtual void onResize(Resolution resolution) {}

    sf::Transform m_transform;
    sf::Transform m_combined_transform;
    std::vector<std::shared_ptr<Node>> m_children;
};
