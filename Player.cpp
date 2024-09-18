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

void Player::move(float boundary, float x, float y){
    std::cout << this->getSprite().getTexture()->getSize().x <<std::endl;
    float xSize = this->getSprite().getTexture()->getSize().x / 2.7;
    float ySize = this->getSprite().getTexture()->getSize().y;
    //right x limit 697
    //left x limit 1
    //y top limit 4
    //y bottom limit 499
    if(this->getSprite().getPosition().x > boundary - xSize){
        this->getSprite().setPosition(sf::Vector2f(boundary-xSize,this->getSprite().getPosition().y));
    } else if(this->getSprite().getPosition().x < 0){
        this->getSprite().setPosition(sf::Vector2f(0.f, this->getSprite().getPosition().y));
    } else if(this->getSprite().getPosition().y > boundary-(ySize*2)){
        this->getSprite().setPosition(sf::Vector2f(this->getSprite().getPosition().x, boundary-(ySize*2)));
    } else if(this->getSprite().getPosition().y < 0){
        this->getSprite().setPosition(sf::Vector2f(this->getSprite().getPosition().x, 0));
    }
    else{
        this->getSprite().move(x,y);
    }
    
}

Bullet* Player::shoot(){
    Bullet* bullet = new Bullet(*this);
    return bullet;
}

void Player::updateHealth(){
    health -= 50;
    this->destroy();
}

void Player::destroy(){
    float xSize = this->getSprite().getTexture()->getSize().x;
    float ySize = this->getSprite().getTexture()->getSize().y;
    this->getSprite().setPosition(sf::Vector2f(xSize+200,ySize-200));
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
