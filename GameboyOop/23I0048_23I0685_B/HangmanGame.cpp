// HangmanGame.cpp
#include "HangmanGame.h"
#include <sstream>
#include <fstream>
#include <iostream>
HangmanGame::HangmanGame(const char* word, const Category& category, int lives) : category(category) {
    this->lives = lives;
    this->streak = 0;
    this->score = 0;
    // Copy word into this->word
    int i = 0;
    while (word[i] != '\0' && i < 9) {
        this->word[i] = word[i];
        i++;
    }
    this->word[i] = '\0';

    // Initialize currentWord with underscores and spaces
    for (int j = 0; j < i; j++) {
        currentWord[j] = (word[j] == ' ') ? ' ' : '_';
    }
    currentWord[i] = '\0';

    for (int k = 0; k < 26; k++) {
        guessedLetters[k] = false;  // By default, nothing is guessed
    }

    // Load the background texture
    if (!backgroundTexture.loadFromFile("hangman.png")) {
        std::cout << "Failed to load background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0, -10);
    backgroundSprite.setScale(3.6,2.8);
    // Load the font for text elements
    if (!font.loadFromFile("a2.otf")) {
        std::cout << "Failed to load font!" << std::endl;
    }

    // Initialize buttons and text elements
    initializeAlphabetButtons();
    initializeTextElements();

    //gameover
    if (!gameOverTexture.loadFromFile("gameover.png")) {
        std::cout << "Failed to load Game Over texture!" << std::endl;
    }
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(300, 200); // Center position
}

void HangmanGame::startGame() {
    std::cout << "Starting Hangman Game..." << std::endl;
    window.create(VideoMode(900, 500), "Hangman Game");
    while (window.isOpen()) {
        handleInput();  // Check for user input and handle it
        render();       // Update the display

        // Check if the word has been guessed correctly
        if (isWordGuessed()) {
            std::cout << "Congratulations! You guessed the word!" << std::endl;
            endGame();   // End the game
            break;
        }

        // Check if the player has run out of lives
        if (getLives() <= 0) {
            std::cout << "Game Over! You ran out of lives." << std::endl;
            endGame();   // End the game
            // Display Game Over screen
            window.draw(gameOverSprite);
            window.display();
            
            break;
        }
    }
}

void HangmanGame::endGame() {
    std::cout << "Ending Hangman Game..." << std::endl;
    window.close();
}

void HangmanGame::render() {
    if (!window.isOpen()) {
        return;
    }

    window.clear(Color::Black);

    // Draw the background
    window.draw(backgroundSprite);

    // Draw the alphabet buttons
    for (int i = 0; i < 26; ++i) {
        window.draw(alphabetButtons[i]);
        window.draw(alphabetText[i]);
    }

    // Draw the word display
    wordDisplay.setString(getCurrentWordDisplay());
    window.draw(wordDisplay);

    // Update stats display
    stringstream ss;
    ss << "Lives: " << getLives() << "\nStreak: " << getStreak() << "\nScore: " << getScore();
    statsDisplay.setString(ss.str());
    window.draw(statsDisplay);

    // Draw the hint button and hint text
    window.draw(hintButton);
    window.draw(hintText);

    // Draw the hangman figure
    drawHangman(window);

    window.display();
}

void HangmanGame::handleInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            endGame();
        }

        if (event.type == Event::MouseButtonPressed) {
            Vector2i mousePos = Mouse::getPosition(window);

            // Check if any alphabet button is pressed
            for (int i = 0; i < 26; ++i) {
                if (alphabetButtons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    char guessedLetter = alphabet[i];
                    trackGuesses(guessedLetter);
                    alphabetButtons[i].setFillColor(Color::Red); // Disable button
                    break;
                }
            }

            // Check if hint button is pressed
            if (hintButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                revealLetter();
            }
        }
    }
}

void HangmanGame::trackGuesses(char guess) {
    if (guessedLetters[guess - 'A']) {
        cout << "Letter already guessed!\n";
        return;
    }

    guessedLetters[guess - 'A'] = true;
    bool found = false;

    // Check if guess is in the word
    for (int i = 0; word[i] != '\0'; i++) {
        if (toupper(word[i]) == guess) {
            currentWord[i] = word[i];
            found = true;
            score += 5; // add 5 to the score for every correct alphabet
        }
    }

    // Update streak based on correctness
    manageStreak(found);

    // Manage lives
    manageLives(found);
}

void HangmanGame::manageLives(bool isCorrect) {
    if (!isCorrect) {
        lives--;
        score -= 2;      //subtract 2 from the score at evry incorrect guess
    }
}

bool HangmanGame::isGuessCorrect(char guess) const {
    for (int i = 0; word[i] != '\0'; i++) {
        if (toupper(word[i]) == guess) {
            return true;
        }
    }
    return false;
}

bool HangmanGame::isWordGuessed() const {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] != currentWord[i]) {
            return false;
        }
    }
    return true;
}

int HangmanGame::getLives() const {
    return lives;
}

int HangmanGame::getStreak() const {
    return streak;
}

const char* HangmanGame::getCurrentWordDisplay() const {
    return currentWord;
}

const char* HangmanGame::getWord() const {
    return word;
}

void HangmanGame::revealLetter() {
    for (int i = 0; word[i] != '\0'; i++) {
        if (currentWord[i] == '_' && !guessedLetters[toupper(word[i]) - 'A']) {
            // Reveal the letter in currentWord
            char revealedLetter = toupper(word[i]);
            for (int j = 0; word[j] != '\0'; j++) {
                if (toupper(word[j]) == revealedLetter) {
                    currentWord[j] = word[j];
                }
            }

            // Mark the letter as guessed
            guessedLetters[revealedLetter - 'A'] = true;
            cout << "Hint revealed letter: " << revealedLetter << "\n";
            return;
        }
    }
    cout << "No more letters to reveal!\n";
}

void HangmanGame::manageStreak(bool isCorrect) {
    if (isCorrect) {
        streak++;
        cout << "Streak increased! Current streak: " << streak << "\n";
    }
    else {
        streak = 0;
        cout << "Streak reset! Current streak: " << streak << "\n";
    }
}

void HangmanGame::drawHangman(sf::RenderWindow& window) {
    hangmanFigure.draw(window, lives); // Delegate to HangmanFigure
}

void HangmanGame::initializeAlphabetButtons() {
    float buttonRadius = 20.0f;
    float startX = 100.0f;
    float startY = 400.0f;
    float offsetX = 50.0f;
    float offsetY = 50.0f;

    for (int i = 0; i < 26; ++i) {
        alphabetButtons[i].setRadius(buttonRadius);
        alphabetButtons[i].setFillColor(Color::White);
        alphabetButtons[i].setOutlineColor(Color::Black);
        alphabetButtons[i].setOutlineThickness(2);

        int row = i / 13;
        int col = i % 13;
        alphabetButtons[i].setPosition(startX + col * offsetX, startY + row * offsetY);

        alphabet[i] = 'A' + i;

        alphabetText[i].setFont(font);
        alphabetText[i].setString(std::string(1, alphabet[i]));
        alphabetText[i].setCharacterSize(24);
        alphabetText[i].setFillColor(Color::Black);
        alphabetText[i].setPosition(alphabetButtons[i].getPosition().x + buttonRadius / 2,
            alphabetButtons[i].getPosition().y + buttonRadius / 4);
    }
}

void HangmanGame::initializeTextElements() {
    // Set up the word display
    wordDisplay.setFont(font);
    wordDisplay.setCharacterSize(32);
    wordDisplay.setFillColor(Color::Black);
    wordDisplay.setPosition(300, 100);
    wordDisplay.setString(getCurrentWordDisplay());

    // Set up the stats display (lives and streak)......and score
    statsDisplay.setFont(font);
    statsDisplay.setCharacterSize(24);
    sf::Color a(255, 165, 0);
    statsDisplay.setFillColor(a);
    statsDisplay.setPosition(700, 60);
    std::stringstream ss;
    ss << "Lives: " << getLives() << "    Streak: " << getStreak() << "Score: " << getScore();
    statsDisplay.setString(ss.str());

    // Set up the hint button
    hintButton.setSize(Vector2f(100, 50));
    hintButton.setFillColor(Color::Yellow);
    hintButton.setPosition(600, 500);

    // Set up the hint text
    hintText.setFont(font);
    hintText.setCharacterSize(20);
    hintText.setFillColor(Color::Black);
    hintText.setString("Hint");
    hintText.setPosition(hintButton.getPosition().x + 25, hintButton.getPosition().y + 10);
}

void HangmanGame::saveGameState(const string& fileName) {
    ofstream outFile(fileName);
    if (!outFile) {
        cerr << "Error: Unable to open file for saving game state.\n";
        return;
    }

    outFile << "Word " << word << "\n";
    outFile << "CurrentWord " << currentWord << "\n";
    outFile << "Lives " << lives << "\n";
    outFile << "GuessedLetters ";
    for (int i = 0; i < 26; ++i) {
        outFile << guessedLetters[i] << " ";
    }
    outFile << "\n";
    outFile << "Streak " << streak << "\n";
    outFile << "Score " << score << "\n";
    outFile.close();
    cout << "Game state saved to " << fileName << "\n";
}


void HangmanGame::loadGameState(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Error: Unable to open file for loading game state.\n";
        return;
    }

    string label;
    inFile >> label >> word;
    if (label != "Word") {
        cerr << "Error: Corrupted file, missing Word label.\n";
        return;
    }

    inFile >> label >> currentWord;
    if (label != "CurrentWord") {
        cerr << "Error: Corrupted file, missing CurrentWord label.\n";
        return;
    }

    inFile >> label >> lives;
    if (label != "Lives") {
        cerr << "Error: Corrupted file, missing Lives label.\n";
        return;
    }

    inFile >> label;
    if (label != "GuessedLetters") {
        cerr << "Error: Corrupted file, missing GuessedLetters label.\n";
        return;
    }
    for (int i = 0; i < 26; ++i) {
        inFile >> guessedLetters[i];
    }

    inFile >> label >> streak;
    if (label != "Streak") {
        cerr << "Error: Corrupted file, missing Streak label.\n";
        return;
    }

    inFile >> label >> score;
    if (label != "Score") {
        cerr << "Error: Corrupted file, missing Score label.\n";
        return;
    }

    inFile.close();
    cout << "Game state loaded from " << fileName << "\n";
}

void HangmanGame::handlePauseResume() {
    static bool isPaused = false;
    isPaused = !isPaused;
    if (isPaused) {
        saveGameState("game_state.txt");
        std::cout << "HangmanGame paused. State saved.\n";
    }
    else {
        loadGameState("game_state.txt");
        std::cout << "HangmanGame resumed. State loaded.\n";
    }
}
