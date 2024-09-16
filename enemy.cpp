#include "enemy.h"

enemy::enemy()
{
}

enemy::enemy(int health, int speed, int location[2], sf::RectangleShape shape)
{
}

sf::RectangleShape enemy::getShape() const
{
    return shape;
}
