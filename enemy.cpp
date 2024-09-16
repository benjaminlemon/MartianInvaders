#include "enemy.h"

enemy::enemy()
{
}

enemy::enemy(int health, int speed, sf::Vector2f position, sf::RectangleShape shape)
{
}

sf::RectangleShape enemy::getShape() const
{
    return shape;
}
