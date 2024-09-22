#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState{
    private:
        GameStateManager& gameStateManager;

    public:
        GameState(GameStateManager& gameStateManager) : {this->gameStateManager = gameStateManager;};

        virtual void handleInput(sf::RenderWindow* &window) = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render(sf::RenderWindow* &window) = 0;

        virtual void initializeState() = 0;
        
        ~GameState() = default;
}
#endif