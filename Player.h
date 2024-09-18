#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"

class Enemy;
class Bullet;
class Player{
    private:
        int health;
        sf::Vector2f position;
        sf::Texture texture;
        
    public:
        sf::Sprite sprite;
        sf::CircleShape shape;
        Player();
        void move(float boundary, float x, float y);
        Bullet* shoot();
        void updateHealth();
        void destroy();
        sf::Vector2f getPosition(){return shape.getPosition();};
        void collides(std::vector<Enemy*> enemies);
        void initializeTexture();
        void initializeSprite();
        sf::Sprite& getSprite(){return sprite;};

};

#endif
