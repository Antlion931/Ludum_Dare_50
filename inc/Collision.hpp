#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <vector>
#include <memory>
#include <string>

class Collider : public Node
{
    union ShapeInfo 
    {
        float radius;
        sf::Vector2f rectangle;
    };

    enum class ShapeType 
    {
        CIRCLE,
        RECTANGLE,
    };

    public:
        ShapeType collision_type;
        ShapeInfo shape_info = {0};
        sf::Vector2f checkCollision(Collider const &other);
        Collider(sf::Vector2f _position, float _radius);
        Collider(sf::Vector2f _position, sf::Vector2f _size);

    private: 
        sf::Vector2f CircleCircle(Collider const &other);
        sf::Vector2f CircleRectangle(Collider const &other);
        sf::Vector2f RectangleCircle(Collider const &other);
        sf::Vector2f RectangleRectangle(Collider const &other);
        void onDrawDebug(sf::RenderTarget &target) const override;
};

class CollisionLayer 
{
    public:
        std::vector<std::shared_ptr<Collider>> list;

};

class Collidable : public Node 
{
    struct CollisionResult 
    {
        std::shared_ptr<Collider> collider;
        sf::Vector2f move_vector;
    };

    public: 
        CollisionResult scanCollisions(int collider_id);
        CollisionResult scanCollisions(int collider_id, std::shared_ptr<CollisionLayer> layer);
        void addCollider(std::shared_ptr<CollisionLayer> layer, sf::Vector2f _position, float _radius);
        void addCollider(std::shared_ptr<CollisionLayer> layer, sf::Vector2f _position, sf::Vector2f _size);
        void addCollider(std::shared_ptr<CollisionLayer> layer, sf::Vector2f _position, float _radius, std::string name);
        void addCollider(std::shared_ptr<CollisionLayer> layer, sf::Vector2f _position, sf::Vector2f _size, std::string name);

    private:
        std::vector<std::shared_ptr<CollisionLayer>> scan_layers;
        std::vector<std::shared_ptr<Collider>> colliders;
};

