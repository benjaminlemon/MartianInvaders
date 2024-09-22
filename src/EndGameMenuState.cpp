#include "../include/GameState.h"
#include "../include/GameStateManager.h"
#include <SFML/Graphics.hpp>

class GameRestartState;

class EndGameMenuState : public GameState {
    private:
        sf::Text textHighScore, textRestart, textExit;
        sf::RectangleShape endGameMenu;

    public:
        EndGameMenuState(GameStateManager& gameStateManager) : GameState(gameStateManager){};
        void handleInput(sf::RenderWindow* &window) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow* &window) override;
        void initializeState() override;
};

void EndGameMenuState::handleInput(sf::RenderWindow* &window){
    sf::Event event;
    while(window->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                break;

            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left){
                    float x = event.mouseButton.x;
                    float y = event.mouseButton.y;

                    if(textExit.getGlobalBounds().contains(x, y)){
                        window->close();
                    }

                    if(textRestart.getGlobalBounds().contains(x,y)){
                        // changestate to play restart
                        gameStateManager.changeGameState(std::make_unique<GameRestartState>(gameStateManager));
                    }
                }

            default:
                break;
        }
    }   
};

void EndGameMenuState::update(float deltaTime)
{

}

void EndGameMenuState::render(sf::RenderWindow* &window)
{
    window->clear(sf::Color::Black);

    window->draw(endGameMenu);
    window->draw(textHighScore);
    window->draw(textExit);
    window->draw(textRestart);
    // music.stop();

    window->display();
}

void EndGameMenuState::initializeState()
{
}
