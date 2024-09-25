#include "GameStateManager.h"
#include "GameState.h"

template <typename derivedGameState>
void GameStateManager::changeGameState(std::unique_ptr<derivedGameState> newState)
{
    if(currentGameState){
        currentGameState->terminateState();
    }

    currentGameState  = std::move(newState);

    if(currentGameState){
        currentGameState->initializeState(window, font);
    }
}