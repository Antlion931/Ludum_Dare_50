#include <Collision.hpp>
#include <Toolkit.hpp>

Collider::Collider(sf::Vector2f _position, float _radius)
{
    setTranslation(_position);
    shape_info.radius = _radius;
    collision_type = ShapeType::CIRCLE;
}

Collider::Collider(sf::Vector2f _position, sf::Vector2f _size)
{
    setTranslation(_position);
    shape_info.rectangle = _size;
    collision_type = ShapeType::RECTANGLE;
}

sf::Vector2f Collider::checkCollision(Collider const &other)
{
    if (collision_type == ShapeType::CIRCLE && other.collision_type == ShapeType::CIRCLE)
    {
        return CircleCircle(other);
    }
    if (collision_type == ShapeType::CIRCLE && other.collision_type == ShapeType::RECTANGLE)
    {
        return CircleRectangle(other);
    }
    if (collision_type == ShapeType::RECTANGLE && other.collision_type == ShapeType::CIRCLE)
    {
        return RectangleCircle(other);
    }
    if (collision_type == ShapeType::RECTANGLE && other.collision_type == ShapeType::RECTANGLE)
    {
        return RectangleRectangle(other);
    }
    return {0, 0};
}

sf::Vector2f Collider::CircleCircle(Collider const &other)
{
    sf::Vector2f s_center = getGlobalTransform().getPosition();
    sf::Vector2f o_center = other.getGlobalTransform().getPosition();
    float s_r = shape_info.radius * getGlobalTransform().getScale().x;
    float o_r = other.shape_info.radius * other.getGlobalTransform().getScale().x;

    if (length(s_center - o_center) < s_r + o_r)
    {
        return norm(s_center - o_center) * (o_r + s_r);
    }
    else
    {
        return {0, 0};
    }
}

sf::Vector2f Collider::CircleRectangle(Collider const &other)
{
    return {0,0};
}
sf::Vector2f Collider::RectangleCircle(Collider const &other)
{
    return {0,0};
}
sf::Vector2f Collider::RectangleRectangle(Collider const &other)
{
    return {0,0};
}
void Collider::onDrawDebug(sf::RenderTarget &target) const
{
    if (collision_type == ShapeType::CIRCLE)
    {
        sf::CircleShape debug_circle = sf::CircleShape(shape_info.radius);
        target.draw(debug_circle, getGlobalTransform().getTransform());
    }
}

Collidable::CollisionResult Collidable::scanCollisions () 
{
    for (const auto& coll : scan_layer->list) 
    {
        if (coll != collider)
        {
            sf::Vector2f result = collider->checkCollision(*coll);
            if(result != sf::Vector2f(0.0,0.0))
                return {coll, result};
        }
    }
    return {NULL, {0,0}};
}


void Collidable::setCollider(std::shared_ptr<CollisionLayer> layer, sf::Vector2f _position, float _radius)
{
    scan_layer = layer;
    std::shared_ptr<Collider> coll = std::make_shared<Collider>(Collider(_position, _radius));
    addChild(coll);
    collider = coll;
    scan_layer->list.push_back(coll);
}

void Collidable::setCollider(std::shared_ptr<CollisionLayer> layer, sf::Vector2f _position, sf::Vector2f _size)
{
    scan_layer = layer;
    std::shared_ptr<Collider> coll = std::make_shared<Collider>(Collider(_position, _size));
    addChild(coll);
    collider = coll;
    scan_layer->list.push_back(coll);
}