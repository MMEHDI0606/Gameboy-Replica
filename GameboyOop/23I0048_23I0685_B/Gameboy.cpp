// Game.cpp - Implement random category and word selection logic
#include "GameBoy.h"
#include "Game.h"
#include "Category.h"
#include "HangmanGame.h"
#include "SnakeGame.h"
#include "WordleGame.h"
#include "Player.h"
#include "leaderboard.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void selectRandomCategoryAndWord(Category& category, char* selectedWord) {
    srand(time(0));
    int randomCategoryIndex = rand() % 3;
    const char oop_category[10][30] = { "inheritance", "polymorphism", "composition", "aggregation", "overloading", "overriding", "constructor", "destructor", "getter", "setter" };
    const char coal_category[10][30] = { "register", "memory", "cache", "address", "binary", "hexadecimal", "assembly", "stack", "offset", "masm" };
    const char discrete_category[10][30] = { "graphs", "proof", "traversal", "nodes", "edges", "trail", "walk", "path", "circuit", "combination" };
    const char* categoryNames[3] = { "OOP", "COAL", "DISCRETE" };

    // Set category name
    const char* selectedCategoryName = categoryNames[randomCategoryIndex];
    category = Category(selectedCategoryName);

    // Select a random word from the chosen category
    const char (*selectedWords)[30] = nullptr;
    switch (randomCategoryIndex) {
    case 0: selectedWords = oop_category; break;
    case 1: selectedWords = coal_category; break;
    case 2: selectedWords = discrete_category; break;
    }
    int randomWordIndex = rand() % 10;

    // Copy the selected word to the provided buffer
    for (int i = 0; i < 30; ++i) {
        selectedWord[i] = selectedWords[randomWordIndex][i];
        if (selectedWords[randomWordIndex][i] == '\0') break; // Stop copying at null terminator
    }

    cout << "Category: " << category.getName() << endl;
    cout << "Selected Word: " << selectedWord << endl;
}

GameBoy::~GameBoy() {
    // Clean up dynamically allocated memory
    delete screen;
    //delete soundSystem;
}
void GameBoy::start(Player& player) {
    RenderWindow window(VideoMode(600, 800), "Gameboy");
    bool isPaused = false; // Tracks whether the game is paused
    int selectedGame = 0;
    Leaderboard leaderboard;
    player.loadProgress();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                shutdown();
                return;
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                if (!isPaused) {
                    // Pause the game
                    isPaused = true;
                    if (currentGame) currentGame->saveGameState("game_state.txt");
                    cout << "Game paused. Press Space to resume." << endl;
                }
                else {
                    // Resume the game
                    isPaused = false;
                    if (currentGame) currentGame->loadGameState("game_state.txt");
                    cout << "Game resumed." << endl;
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (currentGame) {
                    delete currentGame;
                    currentGame = nullptr;
                    selectedGame = 0;
                    cout << "Returning to main menu." << endl;
                }
            }

            if (!isPaused) {
                if (currentGame == nullptr) {
                    menu.handleInput(event, selectedGame);
                    if (selectedGame == 0) {
                        continue;
                    }
                    // Prompt user for name input
                    cout << "Enter your name: ";
                    char playerName[50];
                    cin >> playerName;

                    // Create new player object with the input name
                    Player currentPlayer(playerName);
                    currentPlayer.loadProgress();
            switch (selectedGame) {
            case 1:
                currentGame = new SnakeGame();
                currentGame->startGame();
                currentGame->playsound(1);
                isPaused = false;  


                while (!currentGame->getIsGameOver() && currentGame->getSpeed() > 0) {
                    sf::Event event;

                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            currentGame->stopsound();
                            window.close();
                            return; // Exit the game loop
                        }

                        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                            if (currentGame) {
                                currentGame->handlePauseResume();
                            }
                        }
                    }

                    if (!isPaused) {
                        currentGame->render();
                        currentGame->moveSnake();

                        sf::sleep(milliseconds(currentGame->getSpeed()));

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            currentGame->updateDirection(Game::Direction::UP);
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            currentGame->updateDirection(Game::Direction::DOWN);
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            currentGame->updateDirection(Game::Direction::LEFT);
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            currentGame->updateDirection(Game::Direction::RIGHT);
                        }
                    }
                }

                player.updateHighScore(0, currentGame->getScore());
                delete currentGame; 
                currentGame = nullptr;
                break;



            case 2: {
                Category category;
                char selectedWord[30];
                selectRandomCategoryAndWord(category, selectedWord);
                currentGame = new HangmanGame(selectedWord, category, 6);
                currentGame->playsound(2);
                currentGame->startGame();
                while (window.isOpen()) {
                    Event gameEvent;
                    while (window.pollEvent(gameEvent)) {
                        if (gameEvent.type == Event::Closed) {
                            currentGame->stopsound();
                            window.close();
                        }

                        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                            if (currentGame) {
                                currentGame->handlePauseResume();
                            }
                        }

                        if (!isPaused) {
                            // Handle gameplay-specific input
                           // currentGame->handleInput(gameEvent); // Assume handleInput processes game-specific inputs
                        }
                    }

                    if (!isPaused) {
                        currentGame->render();
                    }
                }

                player.updateHighScore(1, currentGame->getScore());
                delete currentGame; 
                currentGame = nullptr;
                break;
            }


            case 3:
                currentGame = new WordleGame("MAHAM");
                currentGame->startGame();
                currentGame->playsound(3);
                while (currentGame->getWindow().isOpen()) { 
                    sf::Event gameEvent;
                    while (currentGame->getWindow().pollEvent(gameEvent)) {
                        if (gameEvent.type == sf::Event::Closed) {
                            currentGame->stopsound();
                            currentGame->getWindow().close();
                        }

                        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                            if (currentGame) {
                                currentGame->handlePauseResume();
                            }
                        }

                        if (!isPaused) {
                            if (gameEvent.type == sf::Event::TextEntered) {
                                if (gameEvent.text.unicode >= 32 && gameEvent.text.unicode <= 126) {
                                    char inputChar = static_cast<char>(gameEvent.text.unicode);
                                    currentGame->handleCharacterInput(inputChar);
                                }
                            }

                            if (gameEvent.type == sf::Event::KeyPressed) {
                                if (gameEvent.key.code == sf::Keyboard::Enter) {
                                    currentGame->submitGuess();
                                }
                                if (gameEvent.key.code == sf::Keyboard::BackSpace) {
                                    currentGame->deleteLastCharacter();
                                }
                            }
                        }
                    }

                    if (!isPaused) {
                        currentGame->render(); 
                    }
                }

                player.updateHighScore(2, currentGame->getScore());
                delete currentGame; 
                currentGame = nullptr;
                break;
            case 4:
                leaderboard.displayTopScores();  // Display leaderboard
                break;
            default:
                selectedGame = 0;
                break;
            }

            // Check for achievements
            currentPlayer.checkAchievements(currentPlayer);

            // Save player progress
            currentPlayer.saveProgress();

            // Reset selectedGame for next player
            selectedGame = 0;
            delete currentGame;  // Free memory after game completion
            currentGame = nullptr;
                }
            }
        }

            window.clear();
            menu.render(window);
            window.display();
    }
}

void GameBoy::switchGame(Game* game) {
    if (currentGame != nullptr) {
        delete currentGame;
    }
    currentGame = game;
    if (currentGame) {
        currentGame->startGame();
    }
}

void GameBoy::shutdown() {
    if (currentGame) {
        currentGame->endGame();
        delete currentGame;
        currentGame = nullptr;
    }
}


int main() {
    Player player;
    GameBoy gameBoy;
    gameBoy.start(player);
    gameBoy.shutdown();
    return 0;
}