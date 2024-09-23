#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class GameStateManager;

class GameState{
    private:
        GameStateManager& gameStateManager;

    public:
        GameState(GameStateManager& gameStateManager) : gameStateManager(gameStateManager) {};

        virtual void initializeState(sf::RenderWindow* &window, sf::Font font) = 0;

        virtual void handleInput(sf::RenderWindow* &window) = 0;

        virtual void update(float deltaTime) = 0;

        virtual void render(sf::RenderWindow* &window) = 0;

        ~GameState() = default;
};

#endif