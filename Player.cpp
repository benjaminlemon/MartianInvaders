#include "Player.h"

Player::Player(){
    health = 100;
    position = sf::Vector2f(400.f,500.f);
    shape = sf::CircleShape(50.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(position);
}

void Player::move(float x, float y){
    
    shape.move(x,y);
}

void Player::shoot(){
    
}

void Player::updateHealth(){
    
}

void Player::destroy(){
    
}


