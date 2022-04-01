#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Node.hpp"
#include "Toolkit.hpp"

void Node::updateTransform()
{
    if (parent != NULL)
        m_global_transform = combineTransforms(parent->getGlobalTransform(), m_local_transform);
    else
        m_global_transform = m_local_transform;

    for (auto &child : m_children)
    {
        child->updateTransform();
    }
}

void Node::draw(sf::RenderTarget &target) const
{
    // let the node draw itself
    onDraw(target);

    for(auto &child : m_children)
    {
        child ->draw(target);
    }

}

void Node::resize(Resolution resolution)
{
    onResize(resolution);

    for(auto &child : m_children)
    {
        child ->resize(resolution);
    }
}

void Node::addChild(std::shared_ptr<Node> child)
{
    m_children.push_back(child);
    child->parent = this;
    child->updateTransform();
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

void Node::move(sf::Vector2f vec)
{
    m_local_transform.move(vec);
    updateTransform();
}

void Node::rotate(float deegres)
{
    m_local_transform.rotate(deegres);
    updateTransform();
}

void Node::scale(sf::Vector2f vec)
{
    m_local_transform.scale(vec);
    updateTransform();
}

void Node::setScale(sf::Vector2f vec)
{
    m_local_transform.setScale(vec);
    updateTransform();
}

sf::Transformable Node::getGlobalTransform() const
{
    return m_global_transform;
}
