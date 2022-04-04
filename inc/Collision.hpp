#pragma once
#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <vector>
#include <memory>
#include <string>
#include <map>

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
        sf::Vector2f CircleCircle(Collider const &other) const;
        sf::Vector2f CircleRectangle(Collider const &other) const;
        sf::Vector2f RectangleCircle(Collider const &other) const;
        sf::Vector2f RectangleRectangle(Collider const &other) const;
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
        CollisionResult scanCollisions(std::string collider_id);
        //void addCollider(std::shared_ptr<CollisionLayer> coll_layer, std::shared_ptr<CollisionLayer> target_layer, sf::Vector2f _position, float _radius);
        //void addCollider(std::shared_ptr<CollisionLayer> coll_layer, std::shared_ptr<CollisionLayer> target_layer, sf::Vector2f _position, sf::Vector2f _size);
        void addCollider(std::shared_ptr<CollisionLayer> collider_layer, std::shared_ptr<CollisionLayer> scanning_layer, sf::Vector2f _position, float _radius, std::string collider_id);
        void addCollider(std::shared_ptr<CollisionLayer> collider_layer, std::shared_ptr<CollisionLayer> scanning_layer, sf::Vector2f _position, sf::Vector2f _size, std::string collider_id);
        
    protected:
        std::map<std::string, std::shared_ptr<CollisionLayer>> scan_layers;
        std::map<std::string, std::shared_ptr<Collider>> colliders;
};

