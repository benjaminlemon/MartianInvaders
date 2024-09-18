#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
class Player;
class Bullet;

class Enemy{
    private:
        int health, speed;
        sf::Vector2f position;
        sf::Texture texture;
        sf::Sprite sprite;

        void initializeTexture(std::string texturePath);
        void initializeSprite();

    public:
        sf::RectangleShape shape;

        //Constructors
        Enemy();
        Enemy(int health, int speed, sf::Vector2f position, sf::RectangleShape shape);
        
        //setters
        void updatePosition();
        void updateHealth(Bullet* bullet);
        void updateHealth(Player* player);
        void destroy();
        void collides(std::vector<Bullet*> bullets);
        void collides(Player* &player);

        //getters
        sf::RectangleShape getShape()const;
        sf::Vector2f getPosition() const;
        int getHealth(){return health;};
        sf::Sprite getSprite(){return sprite;};
};

#endif
