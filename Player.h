#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Enemy.h"
#include "Game.h"

class Bullet;
class Enemy;
class Player{
    private:
        int health;
        sf::Vector2f position;
        sf::Texture texture;
        
    public:
        bool isPlayerDead;
        sf::Sprite sprite;
        sf::CircleShape shape;
        Player();
        void move(float xBoundary, float yBoundary, float x, float y);
        void updateHealth();
        void destroy();
        sf::Vector2f getPosition(){
            float yOffset = sprite.getTexture()->getSize().y * 1.5;
            float xOffset = sprite.getTexture()->getSize().x / 7;
            
            return sf::Vector2f(sprite.getPosition().x + xOffset,sprite.getPosition().y+yOffset);
        };
        void collides(std::vector<Enemy*> enemies);
        void initializeTexture();
        void initializeSprite();
        sf::Sprite& getSprite(){return sprite;};

};

#endif
