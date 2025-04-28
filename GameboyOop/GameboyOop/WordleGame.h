#ifndef WORDLEGAME_H
#define WORDLEGAME_H

#include "Game.h"
#include "Keyboard.h"
#include "WordDictionary.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

class WordleGame: public Game {
private:
    static constexpr int gridRows = 6;
    static constexpr int gridCols = 5;
    char secretWord[gridCols + 1];          //The word we're trynna guess which in this case is MAHAM
    char grid[gridRows][gridCols];
    char feedback[gridRows][gridCols];       //to store the feedback (coloring the grid boxes)
    int attempts;
    VirtualKeyboard keyboard;
    WordDictionary dictionary;


    sf::RenderWindow window;        
    sf::Font font;                   
    sf::Texture backgroundTexture;    
    sf::Sprite backgroundSprite;     
    sf::Text scoreText;
    char currentGuess[gridCols + 1];  // Current guess that's typed in the row
    int currentLetter;                // Tracks the current letter being entered

    bool compareStrings(const char* str1, const char* str2) const {
        for (int i = 0; i < 6; ++i) {
            char c1 = (str1[i] >= 'a' && str1[i] <= 'z') ? str1[i] - ('a' - 'A') : str1[i];
            char c2 = (str2[i] >= 'a' && str2[i] <= 'z') ? str2[i] - ('a' - 'A') : str2[i];

            if (c1 != c2) return false;
            if (c1 == '\0') break; 
        }
        return true;
    }

public:
    WordleGame(const char* word) : attempts(0), currentLetter(0) {
        for (int i = 0; i < gridCols; ++i) {
            secretWord[i] = word[i];
        }
        secretWord[gridCols] = '\0';

        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                grid[i][j] = '\0';
                feedback[i][j] = '\0'; 
            }
        }

        for (int i = 0; i <= gridCols; ++i) {
            currentGuess[i] = '\0';
        }
        score = 0;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::Red);
    }

    sf::RenderWindow& getWindow() {
        return window;
    }

    static constexpr int getGridRows() { return gridRows; }
    static constexpr int getGridCols() { return gridCols; }
    int getAttempts() const { return attempts; }
    const char* getSecretWord() const { return secretWord; }
    VirtualKeyboard& getKeyboard() override { return keyboard; }

    void updateGrid(char letter, int row, int col) {
        grid[row][col] = letter; 
    }

    void clearRow(int row) {        //func to clear the row in case of invalid word
        for (int col = 0; col < gridCols; ++col) {
            grid[row][col] = '\0'; 
        }
    }

    void giveFeedback(const char* guess) {
        for (int i = 0; i < gridCols; ++i) {
            if (guess[i] == secretWord[i]) {
                feedback[attempts][i] = 'G';  // Correct letter
                keyboard.updateKey(guess[i], 'G');
                score += 10;
            }
            else {
                bool found = false;
                for (int j = 0; j < gridCols; ++j) {
                    if (secretWord[j] == guess[i]) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    feedback[attempts][i] = 'Y';  // Present letter
                    keyboard.updateKey(guess[i], 'Y');
                    score += 5;
                }
                else {
                    feedback[attempts][i] = 'B';  // Incorrect letter
                    keyboard.updateKey(guess[i], 'B');
                }
            }
        }
        attempts++;
    }

    void draw(sf::RenderWindow& window, const sf::Font& font) {
        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                sf::RectangleShape rect(sf::Vector2f(60.f, 60.f));
                rect.setPosition(j * 70.f + 100.f, i * 70.f + 50.f);
                switch (feedback[i][j]) {
                case 'G': rect.setFillColor(sf::Color::Green); break;
                case 'Y': rect.setFillColor(sf::Color::Yellow); break;
                case 'B': rect.setFillColor(sf::Color(128, 128, 128)); break;
                default: rect.setFillColor(sf::Color::White); break;
                }

                window.draw(rect);

                if (grid[i][j] != '\0') {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(grid[i][j]);
                    text.setCharacterSize(30);
                    text.setFillColor(sf::Color::Black);
                    text.setPosition(j * 70.f + 215.f, i * 70.f + 65.f);
                    window.draw(text);
                }
            }
        }
    }

    void handleCharacterInput(char inputChar) {
        if (inputChar >= 'a' && inputChar <= 'z') {
            inputChar = inputChar - ('a' - 'A');
        }

        if (currentLetter < gridCols) { 
            grid[attempts][currentLetter] = inputChar; 
            currentLetter++; // Move to the next position in the row
        }
    }


    void submitGuess() {
        if (currentLetter == gridCols) { // Only submit if the row is complete
            char guess[gridCols + 1];
            for (int i = 0; i < gridCols; ++i) {
                guess[i] = grid[attempts][i];
            }
            guess[gridCols] = '\0'; 
            if (dictionary.validateWord(guess)) { 
                //cout << "DEBUGGIN" << endl;
                giveFeedback(guess); 
                if (compareStrings(guess, secretWord)) {
                    cout << "YOU WINNNNNNNNNNN!" << endl;
                    //endGame();                I WANNA END IT BUT NOT IMMEDIATELY!!!
                }
            }
            else {
                cout << "Invalid word!" << endl;
                clearRow(attempts); 
            }

            currentLetter = 0;
        }
        else {
            cout << "Guess is incomplete!" << endl;
        }
    }

    void deleteLastCharacter() {
        if (currentLetter > 0) { 
            currentLetter--; 
            grid[attempts][currentLetter] = '\0'; 
        }
    }

    void displayScore(sf::RenderWindow& window, const sf::Font& font) {
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::Red);
        scoreText.setPosition(820.f, 20.f); // Top-left corner
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*****************************************START, END, RENDER FUNCTIONS************************************************/
    void startGame() {
        window.create(sf::VideoMode(900, 650), "Wordle Game");

        if (!font.loadFromFile("a1.otf")) {
            cerr << "Error loading font!" << endl;
            return;
        }

        if (!backgroundTexture.loadFromFile("wordle.png")) {
            cerr << "Error" << endl;
            return;
        }
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setPosition(900, 640);
        backgroundSprite.setRotation(180);
        backgroundSprite.setScale(1.1,1);

        stringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
        scoreText.setPosition(100, 20);
        window.draw(scoreText);

        window.display();
    }

    void endGame() {
        cout << "Ending" << endl;
        if (window.isOpen()) {
            window.close();
        }
    }

    void render() {
        if (!window.isOpen()) {
            return;
        }
        window.clear();
        window.draw(backgroundSprite);
        draw(window, font);          
        getKeyboard().draw(window, font); 

        stringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());
        scoreText.setPosition(20.0f, 20.0f);
        window.draw(scoreText);

        window.display();
    }

    void saveGameState(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cout << "Failed to save game state!" << std::endl;
            return;
        }

        // Save the game state in a human-readable format
        outFile << "SecretWord " << secretWord << "\n";
        outFile << "GridRows " << gridRows << "\n";
        outFile << "GridCols " << gridCols << "\n";

        outFile << "Grid\n";
        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                outFile << grid[i][j] << " ";
            }
            outFile << "\n";
        }

        outFile << "Feedback\n";
        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                outFile << feedback[i][j] << " ";
            }
            outFile << "\n";
        }

        outFile << "Attempts " << attempts << "\n";
        outFile << "CurrentGuess " << currentGuess << "\n";
        outFile << "CurrentLetter " << currentLetter << "\n";
        outFile << "Score " << score << "\n";

        outFile.close();
        cout << "Game state saved successfully!" << endl;
    }

    void loadGameState(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Failed to load game state!" << endl;
            return;
        }

        // Read and validate file data
        string label;

        inFile >> label >> secretWord;
        if (label != "SecretWord") {
            cout << "Corrupted file: Missing SecretWord!" << endl;
            return;
        }

        int rows, cols;
        inFile >> label >> rows;
        if (label != "GridRows" || rows != gridRows) {
            cout << "Corrupted file: Invalid GridRows!" << endl;
            return;
        }

        inFile >> label >> cols;
        if (label != "GridCols" || cols != gridCols) {
            cout << "Corrupted file: Invalid GridCols!" << endl;
            return;
        }

        inFile >> label;
        if (label != "Grid") {
            cout << "Corrupted file: Missing Grid!" << endl;
            return;
        }
        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                inFile >> grid[i][j];
            }
        }

        inFile >> label;
        if (label != "Feedback") {
            cout << "Corrupted file: Missing Feedback!" << endl;
            return;
        }
        for (int i = 0; i < gridRows; ++i) {
            for (int j = 0; j < gridCols; ++j) {
                inFile >> feedback[i][j];
            }
        }

        inFile >> label >> attempts;
        if (label != "Attempts") {
            cout << "Corrupted file: Missing Attempts!" << endl;
            return;
        }

        inFile >> label >> currentGuess;
        if (label != "CurrentGuess") {
            cout << "Corrupted file: Missing CurrentGuess!" << endl;
            return;
        }

        inFile >> label >> currentLetter;
        if (label != "CurrentLetter") {
            cout << "Corrupted file: Missing CurrentLetter!" << endl;
            return;
        }

        inFile >> label >> score;
        if (label != "Score") {
            cout << "Corrupted file: Missing Score!" << endl;
            return;
        }

        inFile.close();
        cout << "Game state loaded successfully!" << endl;
    }
    void handlePauseResume() {
        static bool isPaused = false;
        isPaused = !isPaused;
        if (isPaused) {
            saveGameState("game_state.txt");
            std::cout << "WordleGame paused. State saved.\n";
        }
        else {
            loadGameState("game_state.txt");
            std::cout << "WordleGame resumed. State loaded.\n";
        }
    }
};

#endif