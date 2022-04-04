#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "Resolution.hpp"
#include "Toolkit.hpp"

class Node
{
public:
    void updateTransform();
    void updateTransform(sf::Transformable const &parent_transform);
    void draw(sf::RenderTarget &target);
    void update(const sf::Time &delta);
    void resize(Resolution resolution);
    void reset();

    const std::vector<std::shared_ptr<Node>>* getChildren() {return &m_children;}
    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);
    bool isChild(std::shared_ptr<Node> child);

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

    void setActive(bool _active);
    void setVisible(bool _visible);

    bool isActive();
    bool isVisible();

    sf::Transformable m_local_transform;
    sf::Transformable m_global_transform;
protected:
    virtual void onDraw(sf::RenderTarget &target) {}
    virtual void onUpdate(const sf::Time& delta) {};
    virtual void onTransform() {};
    virtual void onResize(Resolution resolution) {}
    virtual void onDrawDebug(sf::RenderTarget &target) const;
    // virtual void onResize(sf::RenderTarget& target) {};

    const Node* parent = NULL;
    std::vector<std::shared_ptr<Node>> m_children;

    bool active = 1;
    bool visible = 1;

private:
    std::string name;

};
