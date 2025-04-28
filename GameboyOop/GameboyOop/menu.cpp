#include "Menu.h"

Menu::Menu() {

    // Load background texture
    if (!backgroundTexture.loadFromFile("game.png")) {
        cerr << "Failed to load background texture!" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(-240, 0);
    backgroundSprite.setScale(3, 2.3);
   
    // Load font
    if (!font.loadFromFile("b2.ttf")) {
        cerr << "Failed to load font!" << endl;
    }

    // Title text
    titleText.setFont(font);
    titleText.setString("GAMEBOY");
    titleText.setCharacterSize(48);
    sf::Color maroon(128, 0, 0);
    titleText.setFillColor(maroon);
    titleText.setPosition(395, 750);
    titleText.setRotation(-20);

    //hehe
    hm.setFont(font);
    hm.setString("Created by Mehdi");
    hm.setCharacterSize(24);
    sf::Color gr(97, 121, 72);
    hm.setFillColor(gr);
    hm.setPosition(25, 400);

    // Snake Game option
    snakeGameText.setFont(font);
    snakeGameText.setString("1 Snake Xenia");
    snakeGameText.setCharacterSize(36);
    snakeGameText.setFillColor(Color::Black);
    snakeGameText.setPosition(200, 120);

    // Hangman Game option
    hangmanGameText.setFont(font);
    hangmanGameText.setString("2 Hangman ");
    hangmanGameText.setCharacterSize(36);
    hangmanGameText.setFillColor(Color::Black);
    hangmanGameText.setPosition(200, 160);

    // Wordle Game option
    wordleGameText.setFont(font);
    wordleGameText.setString("3 Wordle ");
    wordleGameText.setCharacterSize(36);
    wordleGameText.setFillColor(Color::Black);
    wordleGameText.setPosition(200, 200);

    //leaderboard option
    leaderboardText.setFont(font);
    leaderboardText.setString("4 Leaderboard");
    leaderboardText.setCharacterSize(36);
    leaderboardText.setFillColor(Color::Black);
    leaderboardText.setPosition(200, 240);
}

void Menu::render(RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(titleText);
    window.draw(hm);
    window.draw(snakeGameText);
    window.draw(hangmanGameText);
    window.draw(wordleGameText);
    window.draw(leaderboardText);
}

void Menu::handleInput(Event event, int& selectedGame) {
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::Num1) {
            selectedGame = 1; // Snake Game
        }
        else if (event.key.code == Keyboard::Num2) {
            selectedGame = 2; // Hangman Game
        }
        else if (event.key.code == Keyboard::Num3) {
            selectedGame = 3; // Wordle Game
        }
        else if (event.key.code == Keyboard::Num4) {
            selectedGame = 4; // Leaderboard
        }
    }
}
