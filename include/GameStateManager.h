#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H
#include <memory>
#include <SFML/Graphics/Font.hpp>

class GameState;

class GameStateManager{
    private:
        std::unique_ptr<GameState> currentGameState;
        sf::RenderWindow* window;
        sf::Font font;

    public:
        GameStateManager(sf::RenderWindow* window, sf::Font font){this->window = window; this->font = font;};
        void changeGameState(std::unique_ptr<GameState> newState);
        template <typename T>
        std::unique_ptr<GameState> convertState(std::unique_ptr<T> oldState);
};

#endif

template <typename T>
inline std::unique_ptr<GameState> GameStateManager::convertState(std::unique_ptr<T> oldState)
{
    return std::unique_ptr<GameState>(std::make_unique<T> oldState);
}
