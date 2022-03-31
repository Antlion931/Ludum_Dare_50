#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>


class Node
{
public:
    void transform(const sf::Transform& parentTransform)
    {
        m_combined_transform = parentTransform * m_transform;
        for (auto& child : m_children)
        {
            child->transform(m_combined_transform);
        }
    }

    void draw(sf::RenderTarget& target) const
    {
        // let the node draw itself
        onDraw(target, m_combined_transform);

        // draw its children
        for (auto &child : m_children)
            child->draw(target);
    }

    void addChild(std::shared_ptr<Node> child)
    {
        m_children.push_back(child);
        child->transform(m_combined_transform);
    }

    void removeChild(std::shared_ptr<Node> child)
    {
        auto element = std::find(m_children.begin(), m_children.end(), child);
        m_children.erase(element);
    }

    void printChildren()
    {
        std::cout << m_children.size() << std::endl;
    }

protected:

    virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const{}
    //virtual void onResize(sf::RenderTarget& target) {};

    sf::Transform m_transform;
    sf::Transform m_combined_transform;
    std::vector<std::shared_ptr<Node>> m_children;
};