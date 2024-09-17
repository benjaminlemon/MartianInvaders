#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>

class Player{
    private:
        int health;
        sf::Vector2f position;
        
    public:
        sf::CircleShape shape;
        Player();
        void move(float x, float y);
        void shoot();
        void updateHealth();
        void destroy();
        sf::Vector2f getPosition(){return position;};

};

#endif
