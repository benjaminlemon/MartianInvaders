#include "Player.h"


Player::Player(){
    health = 100;
    position = sf::Vector2f(400.f,500.f);
    shape = sf::CircleShape(50.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(position);
}

void Player::move(float x, float y){

    //right x limit 697
    //left x limit 1
    //y top limit 4
    //y bottom limit 499
    if(shape.getPosition().x > 697){
        shape.setPosition(sf::Vector2f(697.f,shape.getPosition().y));
    } else if(shape.getPosition().x < 1){
        shape.setPosition(sf::Vector2f(1.f, shape.getPosition().y));
    } else if(shape.getPosition().y > 499){
        shape.setPosition(sf::Vector2f(shape.getPosition().x, 499.f));
    } else if(shape.getPosition().y < 4){
        shape.setPosition(sf::Vector2f(shape.getPosition().x, 4.f));
    }
    else{
        shape.move(x,y);
    }
    
}

void Player::shoot(){
    
}

void Player::updateHealth(){
    health -= 100;
    this->destroy();
}

void Player::destroy(){
    delete this;
}

void Player::collides(std::vector<Enemy*> enemies){
    for(auto it=enemies.begin(); it != enemies.end(); i++){
        Enemy* enemy = *it;
        if(this->shape.getGlobalBounds().intersects(enemy->shape.getGlobalBounds())){
            this->updateHealth();
        }
    }
}
