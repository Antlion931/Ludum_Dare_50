#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "Resolution.hpp"
#include "Node.hpp"

void Node::resize(Resolution resolution)
{
    onResize(resolution);

    for(auto &child : m_children)
    {
        child ->resize(resolution);
    }
}

void Node::draw(sf::RenderTarget& target) const
{
    // let the node draw itself
    onDraw(target, m_combined_transform);

    // draw its children
    for (auto &child : m_children)
        child->draw(target);
}

void Node::transform(const sf::Transform& parentTransform)
{
    m_combined_transform = parentTransform * m_transform;
    for (auto& child : m_children)
    {
        child->transform(m_combined_transform);
    }
}

void Node::addChild(std::shared_ptr<Node> child)
{
    m_children.push_back(child);
    child->transform(m_combined_transform);
}

void Node::removeChild(std::shared_ptr<Node> child)
{
    auto element = std::find(m_children.begin(), m_children.end(), child);
    m_children.erase(element);
}

void Node::printChildren()
{
    std::cout << m_children.size() << std::endl;
}
