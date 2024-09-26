#ifndef GAME_RUN_STATE_H
#define GAME_RUN_STATE_H

#include <vector>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>

class Player;
class Bullet;
class Enemy;
class GameEndMenuState;
class GameState;

class GameRunState: public GameState{
    private:
        Player* player;
        std::vector<Bullet*> bullets;
        std::vector<Enemy*> enemies;

        sf::Clock gameClock;
        sf::Clock backgroundClock;
        sf::Clock enemySpawnClock;

        sf::Texture backgroundTexture;
        sf::Sprite background1, background2;
        sf::Font font;
        sf::Text scoreText, playerHealthDisplayText;

        sf::Music backgroundMusic;

        bool gameOver = false;
        int score = 0;
        int playerHealthDisplayNum;
        float windowHeight;
        float windowWidth;

        void setWindowDimensions(float windowWidth, float windowHeight){this->windowHeight = windowHeight; this->windowWidth = windowWidth;}; 

        void setFont(sf::Font font){this->font = font;};

        void initializeBackGround();

        void initializeGameScreenText();

        void initializeMusic();

        void spawnEnemies();

        void updateBackground(float deltaTime);

    public:
        GameRunState(sf::RenderWindow* window, sf::Font font);

        void initializeState(sf::RenderWindow* window, sf::Font font);

        void handleInput(sf::RenderWindow* window);

        void update(float deltaTime);

        void render(sf::RenderWindow* window);
};

#endif