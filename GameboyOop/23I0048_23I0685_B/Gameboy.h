#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "Menu.h"
#include "Screen.h"
#include "SoundSystem.h"
#include "Game.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class GameBoy {
public:
    GameBoy() {
        // Set up window and initial game state
        screen = new Screen(); // Allocate memory for screen (or replace with actual screen handling)
        //soundSystem = new SoundSystem();
        currentGame = nullptr;
    }
    ~GameBoy();
    void start(Player& player);
    void switchGame(Game* game);
    void shutdown();
    /*GameBoy(SoundSystem obj);*/

protected:
    Player player; // Composed - GameBoy owns Player, responsible for its lifecycle
    Game* currentGame; // Composed - GameBoy owns currentGame, responsible for its lifecycle
    Menu menu; // Composed - GameBoy owns Menu, responsible for its lifecycle

    // Aggregated - Screen, InputSystem, and SoundSystem are not owned by GameBoy
    Screen* screen;

    //SoundSystem* soundSystem;
};

#endif