#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"

Enemy::Enemy(float windowSizeX)
{
    health = 1;
    speed = 100;
    
    initializeTexture("./textures/Ship1.png");
    initializeSprite();

    width = getSprite().getTexture()->getSize().x;
    height = getSprite().getTexture()->getSize().y;

    position = sf::Vector2f((float)((rand()%(int)(windowSizeX-width)) + (int)width), 0.f);
    sprite.setPosition(position);

}

void Enemy::updatePosition(float dt, float windowHeight, int &enemyScore)
{
    sprite.move(0.f, speed*dt);

    if(sprite.getPosition().y - height> windowHeight){
            markedToDestroy = true;
            enemyScore++;
    }
}

void Enemy::destroy()
{
    delete this;
}

sf::Vector2f Enemy::getPosition() const
{
    return this->position;
}

void Enemy::initializeTexture(std::string texturePath)
{
    if(!texture->loadFromFile(texturePath)){
        std::cerr << "Texture did not load" << std::endl;
    }

    texture->setSmooth(false);
}

void Enemy::initializeSprite()
{
    sprite.setTexture(*texture);
    sprite.rotate(180.f);
}
/* 
void Enemy::updateHealth(Bullet *bullet)
{
    health -= bullet->getDmg();
}

void Enemy::updateHealth(Player *player)
{
    this->health = 0;
}
 */
void Enemy::collides(std::vector<Bullet *> bullets, int &score)
{
    for(auto it = bullets.begin(); it != bullets.end();it++){
        Bullet* bullet = *it;

        if(this->getSprite().getGlobalBounds().intersects(bullet->getSprite().getGlobalBounds())){

            markedToDestroy = true;
            score++;
        }
    }
}

void Enemy::collides(Player* &player)
{
    if(this->getSprite().getGlobalBounds().intersects(player->sprite.getGlobalBounds())){
        // this->updateHealth(player);

        markedToDestroy = true;
    }
}
