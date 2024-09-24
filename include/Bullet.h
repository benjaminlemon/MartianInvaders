#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class Enemy;
class Player;
class Bullet{
    private:
        int dmg;
        int speed;
        sf::RectangleShape shape;
        sf::Vector2f position;
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        sf::Sprite sprite;
        sf::Sound pewPew;
        sf::SoundBuffer soundBuffer;


        void initializeTexture(std::string texturePath);
        void initializeSprite();
        void initializeSound();

    public:
        //data
        bool markedToDestroy = false;

        //Constructors
        Bullet(sf::Vector2f playerPosition);

        //setters
        void updatePosition(float dt);
        void collides(const std::vector<Enemy*> &enemies);
        void destroy();

        //getters
        int getDmg(){return dmg;};
        sf::Vector2f getPosition() const {return position;};
        sf::Sprite& getSprite(){return sprite;};
};

#endif
