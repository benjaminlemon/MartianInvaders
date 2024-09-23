#include "GameState.h"

class Player;
class Enemy;
class Bullet;

class GameRunState: public GameState{
    private:
        Player* player;
        std::vector<Bullet*> bullets;
        std::vector<Enemy*> enemies;

        sf::Clock gameClock;
        sf::Clock backgroundClock;

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

    public:
        GameRunState(GameStateManager& gameStateManager) : GameState(gameStateManager) {};

        void initializeState(sf::RenderWindow * &window, sf::Font font) override;

        void handleInput(sf::RenderWindow* &window) override;

        void update(float deltaTime) override;

        void render(sf::RenderWindow* &window) override;
};

void GameRunState::initializeState(sf::RenderWindow* &window, sf::Font font)
{
    setWindowDimensions(window->getSize().x, window->getSize().y);

    setFont(font);

    initializeBackGround();

    initializeGameScreenText();

    initializeMusic();

}

void GameRunState::initializeBackGround()
{
    //Texture
    if(!backgroundTexture.loadFromFile("../resources/textures/backgroundSpace.png")){
        std::cerr << "Background did not load!" << std::endl;
    }

    backgroundTexture.setSmooth(true);

    //Sprites
    background1.setTexture(backgroundTexture);
    background2.setTexture(backgroundTexture);

    float scaleFactorX = windowWidth/backgroundTexture.getSize().x;
    float scaleFactorY = windowHeight/backgroundTexture.getSize().y;
    background1.setScale(scaleFactorX, scaleFactorY);
    background2.setScale(scaleFactorX, scaleFactorY);

    background2.setPosition(0.f, 0-windowHeight);
}

void GameRunState::initializeGameScreenText()
{
    scoreText.setFont(font);
    playerHealthDisplayText.setFont(font);

    scoreText.setString("Score: ");
    playerHealthDisplayText.setString("Health: ");

    scoreText.setCharacterSize(25);
    playerHealthDisplayText.setCharacterSize(25);

    scoreText.setStyle(sf::Text::Bold);
    playerHealthDisplayText.setStyle(sf::Text::Bold);

    scoreText.setPosition(0,0);
    playerHealthDisplayText.setPosition(0, scoreText.getGlobalBounds().height + 10);
}

void GameRunState::initializeMusic()
{
    if (!backgroundMusic.openFromFile("../resources/sounds/backgroundMusic.ogg")){
    std::cerr << "Music not loaded" << std::endl;
    }
}
