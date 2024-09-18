#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Enemy.h"
#include "Game.h"

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
        void move(float boundary, float x, float y);
        Bullet* shoot();
        void updateHealth();
        void destroy();
        sf::Vector2f getPosition(){
            float offset = sprite.getTexture()->getSize().x/5;
            float x = sprite.getPosition().x + offset;
            float y = sprite.getPosition().y;
            return sf::Vector2f(x,y);
        };
        void collides(std::vector<Enemy*> enemies);
        void initializeTexture();
        void initializeSprite();
        sf::Sprite& getSprite(){return sprite;};

};

#endif
