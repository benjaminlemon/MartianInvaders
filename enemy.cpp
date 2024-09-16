#include "Enemy.h"

Enemy::Enemy()
{
    health = 1;
    speed = 1;
    position = sf::Vector2f(100.f, 100.f);
    shape = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Red);
    
}

Enemy::Enemy(int health, int speed, sf::Vector2f position, sf::RectangleShape shape)
{
}

sf::RectangleShape Enemy::getShape() const
{
    return shape;
}
