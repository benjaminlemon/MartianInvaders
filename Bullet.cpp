#include "Bullet.h"
#include "Player.h"

Bullet::Bullet(Player &player)
{
    dmg = 1;
    speed = 5;
    shape = sf::RectangleShape(sf::Vector2f(5.f, 10.f));
    position = sf::Vector2f(player.getPosition());
}
