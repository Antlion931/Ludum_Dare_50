#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class Node
{
public:
    void updateTransform();

    void draw(sf::RenderTarget &target) const;

    void addChild(std::shared_ptr<Node> child);

    void removeChild(std::shared_ptr<Node> child);

    void printChildren();

    void move(sf::Vector2f vec);

    void rotate(float deegres);

    void scale(sf::Vector2f vec);

    sf::Transformable getGlobalTransform() const;

protected:
    virtual void onDraw(sf::RenderTarget &target) const {}
    // virtual void onResize(sf::RenderTarget& target) {};

    const Node* parent = NULL;
    sf::Transformable m_local_transform;
    sf::Transformable m_global_transform;
    std::vector<std::shared_ptr<Node>> m_children;
};