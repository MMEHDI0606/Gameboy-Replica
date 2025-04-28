// HangmanGame.h
#ifndef HANGMANGAME_H
#define HANGMANGAME_H

#include "Game.h"
#include "HangmanFigure.h"
#include "Category.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class HangmanGame : public Game {
public:
    HangmanGame(const char* word, const Category& category, int lives);
    void trackGuesses(char guess);
    void manageLives(bool isCorrect);
    bool isGuessCorrect(char guess) const;
    bool isWordGuessed() const;
    int getLives() const;
    int getStreak() const;
    const char* getCurrentWordDisplay() const;
    const char* getWord() const;
    void revealLetter();
    void manageStreak(bool isCorrect);
    void drawHangman(sf::RenderWindow& window);

    void startGame() override;
    void render() override;
    void endGame() override;
    void handleInput();
    void saveGameState(const std::string& fileName) override;
    void loadGameState(const std::string& fileName) override;
    void handlePauseResume() override;





private:
    RenderWindow window; // Game window
    Texture backgroundTexture; // Background texture
    Sprite backgroundSprite; // Background sprite

    Texture gameOverTexture;
    Sprite gameOverSprite;

    CircleShape alphabetButtons[26]; // Alphabet buttons
    Text alphabetText[26]; // Text for each alphabet button
    char alphabet[26]; // Array of letters from A-Z

    Font font; // Font for text
    Text wordDisplay; // Text for the current word display
    Text statsDisplay; // Text for displaying lives and streak
    RectangleShape hintButton; // Button for revealing a letter
    Text hintText; // Text for hint button
    Text scoreText;

    char word[10];        // Word to guess
    char currentWord[10]; // Word display with guessed letters
    Category category;
    HangmanFigure hangmanFigure;
    int lives;
    bool guessedLetters[26]; // To track whether each letter is guessed
    int streak;

    void initializeAlphabetButtons();
    void initializeTextElements();
};

#endif


