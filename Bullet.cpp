#include "Bullet.h"
#include "Player.h"

void Bullet::initializeTexture(std::string texturePath)
{
    if(!texture->loadFromFile(texturePath)){
        std::cerr << "Bullet texture did not load" << std::endl;
    }

    texture->setSmooth(false);
}

void Bullet::initializeSprite()
{
    sprite.setTexture(*texture);
    sprite.rotate(-90);
    sprite.scale(1.f,.2f);
}

Bullet::Bullet(sf::Vector2f playerPosition)
{
    dmg = 1;
    speed = 300;
    initializeTexture("./textures/bullets.png");
    initializeSprite();
    float xSize = this->getSprite().getTexture()->getSize().x;
    float ySize = this->getSprite().getTexture()->getSize().y;
    position = sf::Vector2f(playerPosition);
    sprite.setPosition(position);

}

void Bullet::updatePosition(float dt){
    sprite.move(0.f, -speed*dt);

    if(sprite.getPosition().y < 0){
        markedToDestroy = true;
    }
}

void Bullet::collides(const std::vector<Enemy *> &enemies) 
{
    for(Enemy* enemy: enemies){
        if(this->getSprite().getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds())){
            
            markedToDestroy = true;
        }
    }
}

void Bullet::destroy() 
{
    delete this;
};
