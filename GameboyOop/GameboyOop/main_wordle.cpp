//#include "WordleGame.h"
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <cstdlib>
//
//using namespace std;
//
//int main() {
//    WordleGame game("MAHAM");
//    game.startGame();
//
//    while (game.getWindow().isOpen()) {
//        sf::Event event;
//        while (game.getWindow().pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                game.getWindow().close();
//            }
//
//            if (event.type == sf::Event::TextEntered) {
//                if (event.text.unicode >= 32 && event.text.unicode <= 126) {
//                    char inputChar = static_cast<char>(event.text.unicode);
//                    game.handleCharacterInput(inputChar);
//                }
//            }
//
//            if (event.type == sf::Event::MouseButtonPressed) {
//                // Handle mouse press (for keyboard interactions)
//                sf::Vector2i mousePos = sf::Mouse::getPosition(game.getWindow());
//                char keyPressed = game.getKeyboard().getKeyPressed(sf::Vector2f(mousePos));
//                if (keyPressed != '\0') {
//                    game.handleCharacterInput(keyPressed);
//                }
//            }
//
//            if (event.type == sf::Event::KeyPressed) {
//                if (event.key.code == sf::Keyboard::Enter) {
//                    game.submitGuess(); // Process the current guess
//                }
//                if (event.key.code == sf::Keyboard::BackSpace) {
//                    game.deleteLastCharacter(); // Handle backspace
//                }
//            }
//        }
//        //everything's been input at this point and we've pressed enter so this moves on to give feedbck or clearing the row
//        game.render(); 
//    }
//
//    return 0;
//}
