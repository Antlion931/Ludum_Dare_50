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

sf::Vector2f Collider::CircleCircle(Collider const &other) const
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

sf::Vector2f Collider::CircleRectangle(Collider const &other) const 
{
    sf::Vector2f s_center = getGlobalTransform().getPosition();
    float s_radius =  shape_info.radius * getGlobalTransform().getScale().x;

    sf::Vector2f o_center = other.getGlobalTransform().getPosition();
    sf::Vector2f o_top_left = {o_center.x - other.shape_info.rectangle.x/2 * other.getGlobalTransform().getScale().x, o_center.y - other.shape_info.rectangle.y/2 * other.getGlobalTransform().getScale().y};
    sf::Vector2f o_top_right = {o_center.x + other.shape_info.rectangle.x/2 * other.getGlobalTransform().getScale().x, o_center.y - other.shape_info.rectangle.y/2 * other.getGlobalTransform().getScale().y};
    sf::Vector2f o_bottom_left = {o_center.x - other.shape_info.rectangle.x/2 * other.getGlobalTransform().getScale().x, o_center.y + other.shape_info.rectangle.y/2 * other.getGlobalTransform().getScale().y};
    sf::Vector2f o_bottom_right = {o_center.x + other.shape_info.rectangle.x/2 * other.getGlobalTransform().getScale().x, o_center.y + other.shape_info.rectangle.y/2 * other.getGlobalTransform().getScale().y};

    sf::Vector2f min_dist_point = closestPointToLine(o_top_left, o_top_right, s_center);
    if (length_squared(min_dist_point - s_center) > length_squared(closestPointToLine(o_top_right, o_bottom_right, s_center) - s_center))
        min_dist_point = closestPointToLine(o_top_right, o_bottom_right, s_center);
    if (length_squared(min_dist_point - s_center) > length_squared(closestPointToLine(o_bottom_right, o_bottom_left, s_center) - s_center))
        min_dist_point = closestPointToLine(o_bottom_right, o_bottom_left, s_center);
    if (length_squared(min_dist_point - s_center) > length_squared(closestPointToLine(o_bottom_left, o_top_left, s_center) - s_center))
        min_dist_point = closestPointToLine(o_bottom_left, o_top_left, s_center);

    if (s_center.x > o_top_left.x && s_center.x < o_bottom_right.x && s_center.y > o_top_left.y && s_center.y < o_bottom_right.y)
    {
        return norm(min_dist_point - s_center) * (s_radius + length(s_center - min_dist_point));
    }

    if (length(min_dist_point - s_center) < s_radius)
    {
        return norm(s_center - min_dist_point) * (s_radius - length(s_center - min_dist_point)); 
    }
    else
    {
        return {0,0};
    }
}
sf::Vector2f Collider::RectangleCircle(Collider const &other) const
{
    return -1.0f * other.CircleRectangle(*this);
}
sf::Vector2f Collider::RectangleRectangle(Collider const &other) const
{
    sf::Vector2f s_center = getGlobalTransform().getPosition();
    float s_x_left = s_center.x - shape_info.rectangle.x/2 * getGlobalTransform().getScale().x;
    float s_x_right = s_center.x + shape_info.rectangle.x/2 * getGlobalTransform().getScale().x;
    float s_y_bottom = s_center.y + shape_info.rectangle.y/2 * getGlobalTransform().getScale().x;
    float s_y_top = s_center.y - shape_info.rectangle.y/2 * getGlobalTransform().getScale().x;
    
    sf::Vector2f o_center = other.getGlobalTransform().getPosition();
    float o_x_left = o_center.x - other.shape_info.rectangle.x/2 * other.getGlobalTransform().getScale().x;
    float o_x_right = o_center.x + other.shape_info.rectangle.x/2 * other.getGlobalTransform().getScale().x;
    float o_y_bottom = o_center.y + other.shape_info.rectangle.y/2 * other.getGlobalTransform().getScale().x;
    float o_y_top = o_center.y - other.shape_info.rectangle.y/2 * other.getGlobalTransform().getScale().x;

    if(s_x_left > o_x_right || s_x_right < o_x_left || s_y_bottom < o_y_top || s_y_top > o_y_bottom)
        return {0,0};
    
    return {1,1};

}
void Collider::onDrawDebug(sf::RenderTarget &target) const
{
    Node::onDrawDebug(target);
    if (collision_type == ShapeType::CIRCLE)
    {
        sf::CircleShape debug_circle = sf::CircleShape(shape_info.radius);
        debug_circle.setFillColor(sf::Color(100, 100, 100, 70));
        debug_circle.move(-shape_info.radius, -shape_info.radius);
        target.draw(debug_circle, getGlobalTransform().getTransform());
    }
    else if (collision_type == ShapeType::RECTANGLE)
    {
        sf::RectangleShape debug_rect = sf::RectangleShape(shape_info.rectangle);
        debug_rect.setFillColor(sf::Color(100, 100, 100, 70));
        debug_rect.move(-shape_info.rectangle.x/2, -shape_info.rectangle.y/2);
        target.draw(debug_rect, getGlobalTransform().getTransform());
    }
}

Collidable::CollisionResult Collidable::scanCollisions (std::string collider_id) 
{
    std::set<std::string> collision_names;
    sf::Vector2f move_vector = {0,0};
    
    if (!scan_layers.contains(collider_id) or scan_layers[collider_id] == nullptr)
        return {collision_names, move_vector};
    
    for (const auto& coll : scan_layers[collider_id]->list) 
    {
        if (coll != colliders[collider_id] && coll->isActive())
        {
            sf::Vector2f result = colliders[collider_id]->checkCollision(*coll);
            if(result != sf::Vector2f(0.0,0.0))
            {
                move_vector = move_vector + result;
                collision_names.insert(coll->getName());
            }
        }
    }
    return {collision_names, move_vector};
}

void Collidable::addCollider(std::shared_ptr<CollisionLayer> collider_layer, std::shared_ptr<CollisionLayer> scanning_layer, sf::Vector2f _position, float _radius, std::string collider_id)
{
    scan_layers[collider_id] = scanning_layer;
    std::shared_ptr<Collider> coll = std::make_shared<Collider>(Collider(_position, _radius));
    coll->setName(collider_id);
    addChild(coll);
    colliders[collider_id] = coll;
    if(collider_layer != nullptr)
        collider_layer->list.push_back(coll);
}
void Collidable::addCollider(std::shared_ptr<CollisionLayer> collider_layer, std::shared_ptr<CollisionLayer> scanning_layer, sf::Vector2f _position, sf::Vector2f _size, std::string collider_id)
{
    scan_layers[collider_id] = scanning_layer;
    std::shared_ptr<Collider> coll = std::make_shared<Collider>(Collider(_position, _size));
    coll->setName(collider_id);
    addChild(coll);
    colliders[collider_id] = coll;
    if(collider_layer != nullptr)
        collider_layer->list.push_back(coll);
}