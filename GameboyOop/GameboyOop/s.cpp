//#include "Gameboy.h"
//#include "SnakeGame.h"
//#include "HangmanGame.h"
//#include "WordleGame.h"
//#include <iostream>
//
//using namespace std;
//
//GameBoy::GameBoy() {
//    screen = new Screen();
//    soundSystem = new SoundSystem();
//    currentGame = nullptr;
//}
//
//GameBoy::~GameBoy() {
//    delete screen;
//    delete soundSystem;
//}
//
//void GameBoy::start(Player& player) {
//    RenderWindow window(VideoMode(600, 800), "Gameboy");
//    bool isPaused = false;
//    int selectedGame = 0;
//    Leaderboard leaderboard;
//    player.loadProgress();
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                shutdown();
//                return;
//            }
//
//            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
//                if (!isPaused) {
//                    isPaused = true;
//                    if (currentGame) currentGame->saveGameState("game_state.txt");
//                    cout << "Game paused. Press Space to resume." << endl;
//                }
//                else {
//                    isPaused = false;
//                    if (currentGame) currentGame->loadGameState("game_state.txt");
//                    cout << "Game resumed." << endl;
//                }
//            }
//
//            if (!isPaused) {
//                if (currentGame == nullptr) {
//                    menu.handleInput(event, selectedGame);
//                }
//                else {
//                    if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//                        // Escape pressed, return to menu
//                        delete currentGame;
//                        currentGame = nullptr;
//                        selectedGame = 0;
//                        cout << "Returning to main menu." << endl;
//                        continue;
//                    }
//                }
//            }
//        }
//
//        if (currentGame == nullptr && selectedGame != 0) {
//            switch (selectedGame) {
//            case 1:
//                currentGame = new SnakeGame();
//                break;
//            case 2: {
//                Category category;
//                char selectedWord[30];
//                selectRandomCategoryAndWord(category, selectedWord);
//                currentGame = new HangmanGame(selectedWord, category, 6);
//                break;
//            }
//            case 3:
//                currentGame = new WordleGame("MAHAM");
//                break;
//            case 4:
//                leaderboard.displayTopScores();
//                break;
//            default:
//                selectedGame = 0;
//                break;
//            }
//
//            if (currentGame) {
//                currentGame->startGame();
//            }
//        }
//
//        window.clear();
//        if (currentGame == nullptr) {
//            menu.render(window);
//        }
//        else {
//            currentGame->render();
//        }
//        window.display();
//    }
//}
//
//void GameBoy::shutdown() {
//    if (currentGame) {
//        currentGame->endGame();
//        delete currentGame;
//        currentGame = nullptr;
//    }
//}
//
//int main() {
//    Player player;
//    GameBoy gameBoy;
//    gameBoy.start(player);
//    gameBoy.shutdown();
//    return 0;
//}