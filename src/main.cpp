#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameState.h"
#include "GameRunState.h"

int main(){
    Game game = Game();
    game.currentState->initializeState(game.window, game.font);

    float elaspsedTime = game.gameClock.getElapsedTime().asSeconds();

    while(game.window->isOpen()){
        game.currentState->handleInput(game.window);
        game.currentState->update(elaspsedTime);
        game.currentState->render(game.window);
    }
    return 0;
}

