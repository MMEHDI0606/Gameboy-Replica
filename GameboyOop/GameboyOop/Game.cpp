#include "Game.h"
#include "SnakeGame.h"

void Game::startGame() {
    //empty since it is purely abstract
}

void Game::endGame() {
    //empty since it is purely abstract
}

void Game::render() {
    //empty since it is purely abstract
}
void Game::playsound(int x)
{
    while (x > 3 || x < 1)
    {
        cout << "Must be between 1 to 3";
        cin >> x;
    }
    switch (x)
    {
    case 1:
        soundSystem.playMusic("../Sounds/Snake.wav",true);
        break;
    case 2:
        //play hangman
        soundSystem.playMusic("../Sounds/Hang.wav",true);
    case 3:
        //play wordle
        soundSystem.playMusic("../Sounds/Wordle.wav",true);
    default:
        break;
    }
}

void Game::stopsound()
{
    soundSystem.stopMusic();
}