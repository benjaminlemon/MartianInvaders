#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>

class Enemy{
    private:
        int health, speed;
        sf::Vector2f position;
    public:
        sf::RectangleShape shape;
        Enemy();
        Enemy(int health, int speed, sf::Vector2f position, sf::RectangleShape shape);
        //setters
        void updatePosition();
        void updateHealth();
        void destroy();

        //getters
        sf::RectangleShape getShape()const;
        sf::Vector2f getPosition() const;
};

#endif