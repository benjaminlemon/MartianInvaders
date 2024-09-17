#include "Enemy.h"

Enemy::Enemy()
{
    health = 1;
    speed = 1;
    position = sf::Vector2f(400.f, 400.f);
    shape = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    
}

Enemy::Enemy(int health, int speed, sf::Vector2f position, sf::RectangleShape shape)
{
}

sf::RectangleShape Enemy::getShape() const
{
    return shape;
}

void Enemy::updatePosition()
{
    position+=sf::Vector2f(0,(float)speed);
    shape.setPosition(position);
}


void Enemy::destroy()
{
    delete this;
}

sf::Vector2f Enemy::getPosition() const
{
    return this->position;
}