#include "GameState.h"

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

        void initializeBackGround()
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

        void initializeGameScreenText()
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

        void initializeMusic()
        {
            if (!backgroundMusic.openFromFile("../resources/sounds/backgroundMusic.ogg")){
            std::cerr << "Music not loaded" << std::endl;
            }
        }

        void spawnEnemies()
{
    Enemy* enemy = new Enemy(windowWidth);
    enemies.push_back(enemy);
}


    public:
        GameRunState(GameStateManager& gameStateManager) : GameState(gameStateManager) {};

        void initializeState(sf::RenderWindow * &window, sf::Font font) override{
            setWindowDimensions(window->getSize().x, window->getSize().y);

            setFont(font);

            initializeBackGround();

            initializeGameScreenText();

            initializeMusic();

            //init game objs
            player = new Player();
            spawnEnemies();
        };

        void handleInput(sf::RenderWindow* &window) override {
            sf::Event event;

            while(window->pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed:
                        window->close();
                        break;
                    
                    case sf::Event::KeyPressed:
                        if(event.key.scancode == sf::Keyboard::Scan::A){
                            player->getSprite().setTextureRect(sf::IntRect(31,0,30,32));
                        }
                        else if(event.key.scancode == sf::Keyboard::Scan::D){
                            player->getSprite().setTextureRect(sf::IntRect(92,0,29,32));
                        }
                        break;
                    
                    case sf::Event::KeyReleased:
                        if(event.key.scancode == sf::Keyboard::Scan::A || event.key.scancode == sf::Keyboard::Scan::D){
                            player->getSprite().setTextureRect(sf::IntRect(59,0,30,32));
                        }
                        break;

                    default:
                        break;
                }
            }   

            //smooth movement with keyboard
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                player->move(windowWidth,windowHeight,-1,0);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player->move(windowWidth,windowHeight,1,0);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                player->move(windowWidth,windowHeight,0,-1);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player->move(windowWidth,windowHeight,0,1);
            }
            
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                bullets.push_back(player->shoot());
            }
        };

        void update(float deltaTime) override;

        void render(sf::RenderWindow* &window) override;
};
};