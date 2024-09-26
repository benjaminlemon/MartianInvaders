#include "Game.h"


//Game
//GameRunState
void Game::initialize()
{
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Martian Invasion");
    //frame rate == monitor refresh to prevent tearing
    window->setVerticalSyncEnabled(true);

    initializeFont();

    currentState = new GameRunState(window, font);
}


Game::Game()
{
    initialize();
};

//Game or main? want same font for all of the game I think...
void Game::initializeFont()
{
    if (!font.loadFromFile("resources/fonts/PixelifySans-Regular.ttf"))
    {
        std::cerr << "Font did not load!" << std::endl;
    }
};