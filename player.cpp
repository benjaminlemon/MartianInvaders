#include "player.h"

player::player(){
    health = 100;
    position = sf::Vector2f(400.f,500.f);
    shape = sf::CircleShape(75.f);
    shape.setFillColor(sf::Color::Blue);
}

player::player(int health, sf::Vector2f position, sf::CircleShape shape){
    this->health = health;
    this->position = position;
    this->shape = shape;
    
}

void player::move(float x, float y){
    shape.move(x,y);
}

void player::shoot(){
    
}

void player::updateHealth(){
    
}

void player::destroy(){
    
}


