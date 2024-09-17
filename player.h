#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>

class player{
    private:
        int health;
        sf::Vector2f position;
        
    public:
        sf::CircleShape shape;
        player();
        player(int health, sf::Vector2f position, sf::CircleShape shape);
        void move(float x, float y);
        void shoot();
        void updateHealth();
        void destroy();
};

#endif
