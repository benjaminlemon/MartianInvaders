#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include "Game.h"

class Player;
class Bullet;
class Game;

class Enemy{
    private:
        int health;
        float speed;
        float width;
        float height;
        sf::Vector2f position;
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        sf::Sprite sprite;

        void initializeTexture(std::string texturePath);
        void initializeSprite();

    public:
        bool markedToDestroy = false;
        //Constructors
        Enemy(float windowSizeX);
        Enemy(int health, int speed, sf::Vector2f position, std::string texturePath);
        
        //setters
        void updatePosition(float dt, float windowHeight, int &enemyScore);
        void updateHealth(Bullet* bullet);
        void updateHealth(Player* player);
        void destroy();
        void collides(std::vector<Bullet*> bullets, int &score);
        void collides(Player* &player);

        //getters
        sf::Vector2f getPosition() const;
        int getHealth(){return health;};
        sf::Sprite& getSprite(){return sprite;};
};

#endif
