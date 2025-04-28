#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Keyboard.h"
#include "SoundSystem.h" // Added for sound integration
using namespace sf;
using namespace std;

class VirtualKeyboard;

class Game {
public:
    virtual void startGame() = 0;
    virtual void endGame() = 0;
    virtual void render() = 0;


    /************************FUNCTIONS FOR SNAKE**********************************/
    enum class Direction { UP, DOWN, LEFT, RIGHT };
    virtual void moveSnake() {}
    virtual void updateDirection(Direction newDirection) {}
    virtual int getSpeed() const { return 0; }
    virtual bool getIsGameOver() { return false; }

    /*************sound ***********FUNCTIONS FOR WORDLE**********************************/
    virtual sf::RenderWindow& getWindow() { 
        static sf::RenderWindow defaultWindow;  // This will return a default window
        return defaultWindow;
    }
    virtual void handleCharacterInput(char inputChar) { }
    virtual ~Game() {}
    virtual VirtualKeyboard& getKeyboard() { 
        static VirtualKeyboard defaultKeyboard;  // This will return a default keyboard
        return defaultKeyboard;
    }  
    virtual void submitGuess(){}
    virtual void deleteLastCharacter(){}

    /**************************FUNCTIONS FOR GAME STATE**********************************/
    virtual void saveGameState(const std::string& fileName) = 0;
    virtual void loadGameState(const std::string& fileName) = 0;
    virtual void handlePauseResume() = 0;
    /**************************SOUND SYSTEM FUNCTIONS***********************************/
    void playsound(int x);
    void stopsound();

protected:
    char name[20];
    int score;
    SoundSystem soundSystem; // aggregated SoundSystem object
public:
    int getScore() const {
        return score;
    }
};

#endif