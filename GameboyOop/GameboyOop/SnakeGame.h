#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include "Game.h"

using namespace sf;
using namespace std;

// Enum for snake direction
enum Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame : public Game {
public:
    SnakeGame();
    void startGame() override;
    void endGame() override;
    void render() override;
    void moveSnake();
    void detectCollision();
    void increaseDifficulty();
    void updateDirection(Game::Direction newDirection);
    int speed; // Speed of the game (in milliseconds)
    int getSpeed() const override { return speed; }
    bool getIsGameOver() const;

private:
    int snakeBody[100][2]; // Snake segment positions
    int food[2]; // Food position
    int gridWidth = 50; // Grid width
    int gridHeight = 30; // Grid height
    int snakeLength; // Length of the snake
    Direction direction; // Current direction of the snake
    RenderWindow window; // SFML window for rendering

    // Textures and Sprites
    Texture headTexture;
    Sprite headSprite;
    Texture bodyTexture;
    Sprite bodySprite;
    Texture tailTexture;
    Sprite tailSprite;
    Texture foodTexture;
    Sprite foodSprite;
    Texture wallTexture;
    Sprite wallSprite;

    Texture backgroundTexture; // Texture for the background
    Sprite backgroundSprite; // Sprite for the background
    Font font; // Font for displaying text
    Text scoreText; // Text for displaying the score
    Texture gameOverTexture;
    Sprite gameOverSprite;
    void saveGameState(const std::string& fileName) override;
    void loadGameState(const std::string& fileName) override; 
    void handlePauseResume() override;
    bool isGameOver;
};

#endif // SNAKEGAME_H
