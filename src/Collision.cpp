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
        return (norm(s_center - o_center) * (o_r + s_r - length(s_center - o_center)));
    }
    else
    {
        return {0, 0};
    }
}

sf::Vector2f Collider::CircleRectangle(Collider const &other)
{
    sf::Vector2f s_center = getGlobalTransform().getPosition();
    float s_radius =  shape_info.radius;

    sf::Vector2f o_center = other.getGlobalTransform().getPosition();
    sf::Vector2f o_top_left = {o_center.x - shape_info.rectangle.x/2, o_center.y - shape_info.rectangle.y/2};
    sf::Vector2f o_top_right = {o_center.x + shape_info.rectangle.x/2, o_center.y - shape_info.rectangle.y/2};
    sf::Vector2f o_bottom_left = {o_center.x - shape_info.rectangle.x/2, o_center.y + shape_info.rectangle.y/2};
    sf::Vector2f o_bottom_right = {o_center.x + shape_info.rectangle.x/2, o_center.y + shape_info.rectangle.y/2};

    
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
    Node::onDrawDebug(target);
    if (collision_type == ShapeType::CIRCLE)
    {
        sf::CircleShape debug_circle = sf::CircleShape(shape_info.radius);
        debug_circle.setFillColor(sf::Color(20, 100, 100, 50));
        debug_circle.move(-shape_info.radius, -shape_info.radius);
        target.draw(debug_circle, getGlobalTransform().getTransform());
    }
    else if (collision_type == ShapeType::RECTANGLE)
    {
        sf::RectangleShape debug_rect = sf::RectangleShape(shape_info.rectangle);
        debug_rect.setFillColor(sf::Color(20, 100, 100, 50));
        debug_rect.move(-shape_info.rectangle.x/2, -shape_info.rectangle.y/2);
        target.draw(debug_rect, getGlobalTransform().getTransform());
    }
}

Collidable::CollisionResult Collidable::scanCollisions () 
{
    std::shared_ptr<Collider> last_collision = nullptr;
    sf::Vector2f move_vector = {0,0};
    for (const auto& coll : scan_layer->list) 
    {
        if (coll != collider && coll->isActive())
        {
            sf::Vector2f result = collider->checkCollision(*coll);
            if(result != sf::Vector2f(0.0,0.0))
            {
                move_vector = move_vector + result;
                last_collision = coll;
            }
        }
    }
    return {last_collision, move_vector};
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