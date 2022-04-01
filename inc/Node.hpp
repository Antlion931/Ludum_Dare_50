#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Resolution.hpp"

class Node
{
public:
    void updateTransform();
    void draw(sf::RenderTarget &target) const;
    void resize(Resolution resolution);

    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);

    void translate(sf::Vector2f vec);
    void setTranslation(sf::Vector2f vec);
    void rotate(float deegres);
    void setRotation(float deegres);
    void scale(sf::Vector2f vec);
    void setScale(sf::Vector2f vec);

    std::string getName() {return name;}
    void setName(std::string new_name) {name = new_name;}
    void printTree(int depth);
    void printTree() {printTree(0);}

    sf::Transformable getGlobalTransform() const;

    bool debug_visible = true;
    virtual void printDebug() const;

protected:
    virtual void onDraw(sf::RenderTarget &target) const {}
    virtual void onResize(Resolution resolution) {}
    virtual void onDrawDebug(sf::RenderTarget &target) const {}
    // virtual void onResize(sf::RenderTarget& target) {};

    const Node* parent = NULL;
    sf::Transformable m_local_transform;
    sf::Transformable m_global_transform;
    std::vector<std::shared_ptr<Node>> m_children;

private:
    std::string name;

};
