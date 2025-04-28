#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Menu {
public:
    Menu();
    void render(RenderWindow& window);
    void handleInput(Event event, int& selectedGame);

private:
    Font font;
    Text titleText;
    Text hm;
    Text snakeGameText;
    Text hangmanGameText;
    Text wordleGameText;
    Text leaderboardText;
    Texture backgroundTexture; // Texture for the background
    Sprite backgroundSprite;   // Sprite for the background
};

#endif // MENU_H
