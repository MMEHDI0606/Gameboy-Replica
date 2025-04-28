#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "Game.h"

using namespace sf;
using namespace std;

class Screen {
public:
    void render();
    void render(Menu menu); // Renders the Menu object on the screen
    void render(Game& game); // Renders the Game object on the screen
    void manageState();

private:
    int resolutionX;
    int resolutionY;
    char buffer[1024]; // buffer for storing pixels
    RenderWindow window; // sfml object to render a window
};

#endif
