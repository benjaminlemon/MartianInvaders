#include "Player.h"


Player::Player(){
    health = 100;
    position = sf::Vector2f(400.f,500.f);
    // this->getSprite() = sf::Circlethis->getSprite()(50.f);
    // this->getSprite().setFillColor(sf::Color::Blue);
    // this->getSprite().setPosition(position);
    initializeTexture();
    initializeSprite();
    sprite.setPosition(position);
}

void Player::move(float x, float y){

    //right x limit 697
    //left x limit 1
    //y top limit 4
    //y bottom limit 499
    if(sprite.getPosition().x > 697){
        this->sprite.setPosition(sf::Vector2f(697.f,this->getSprite().getPosition().y));
    } else if(this->getSprite().getPosition().x < 1){
        this->getSprite().setPosition(sf::Vector2f(1.f, this->getSprite().getPosition().y));
    } else if(sprite.getPosition().y > 499){
        sprite.setPosition(sf::Vector2f(sprite.getPosition().x, 499.f));
    } else if(this->getSprite().getPosition().y < 4){
        this->getSprite().setPosition(sf::Vector2f(this->getSprite().getPosition().x, 4.f));
    }
    else{
        this->getSprite().move(x,y);
    }
    
}

// Bullet* Player::shoot(){
//     Bullet* bullet = new Bullet(*this);
//     return bullet;
// }

void Player::updateHealth(){
    health -= 100;
    this->destroy();
}

void Player::destroy(){
    shape.setPosition(sf::Vector2f(1000.f,1000.f));
}

void Player::collides(std::vector<Enemy*> enemies){
    for(auto it=enemies.begin(); it != enemies.end(); it++){
        Enemy* enemy = *it;
        if(this->getSprite().getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds())){
            this->updateHealth();
        }
    }
}

void Player::initializeTexture()
{
    if(!texture.loadFromFile("./textures/combatjet-32x32.png")){
        std::cerr << "Could not load player texture!" << std::endl;
    };
    texture.setSmooth(false);
}

void Player::initializeSprite()
{
    sprite.setTexture(texture);

    sprite.setTextureRect(sf::IntRect(59,0,30,32));

    sprite.scale(2.f, 2.f);
}
