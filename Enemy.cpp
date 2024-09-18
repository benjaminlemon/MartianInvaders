#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

Enemy::Enemy()
{
    health = 1;
    speed = 2;
    position = sf::Vector2f((float)(rand()%751), 0.f);
    // shape = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    // shape.setFillColor(sf::Color::Red);
    sprite.setPosition(position);
    initializeTexture("./textures/Ship1.png");
    initializeSprite();
}

Enemy::Enemy(int health, int speed, sf::Vector2f position, sf::RectangleShape shape)
{
}

void Enemy::updatePosition()
{
    position+=sf::Vector2f(0,(float)speed);
    sprite.setPosition(position);

    //update to include OOB?
}

void Enemy::destroy()
{
    delete this;
}

sf::Vector2f Enemy::getPosition() const
{
    return this->position;
}

sf::RectangleShape Enemy::getShape() const
{
    return shape;
}

void Enemy::initializeTexture(std::string texturePath)
{
    if(!texture.loadFromFile(texturePath)){
        std::cerr << "Texture did not load" << std::endl;
    }

    texture.setSmooth(false);
}

void Enemy::initializeSprite()
{
    sprite.setTexture(texture);
    sprite.rotate(180.f);
}

void Enemy::updateHealth(Bullet *bullet)
{
    health -= bullet->getDmg();
}

void Enemy::updateHealth(Player *player)
{
    this->health = 0;
}

void Enemy::collides(std::vector<Bullet *> bullets)
{
    for(auto it = bullets.begin(); it != bullets.end();it++){
        Bullet* bullet = *it;

        if(this->shape.getGlobalBounds().intersects(bullet->getShape().getGlobalBounds())){
            this->updateHealth(bullet);
        }
    }
}

void Enemy::collides(Player* &player)
{
    if(this->shape.getGlobalBounds().intersects(player->shape.getGlobalBounds())){
    this->updateHealth(player);
    }
}
