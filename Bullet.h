#ifndef BULLET_H
#define BULLET_H

class Bullet{
    private:
        int dmg;
        int speed; 
        sf::Vector2f position;
        sf::RectangleShape shape;

    public:
        Bullet();
        void updatePosition();
        void destroy();
};

#endif