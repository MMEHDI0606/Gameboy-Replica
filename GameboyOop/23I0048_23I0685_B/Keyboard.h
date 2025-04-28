#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Graphics.hpp>

using namespace std;

class VirtualKeyboard {
private:
    char keys[26];
    sf::RectangleShape keyRects[26]; // 26 boxes cuz 26 alphabets

public:
    VirtualKeyboard() {
        float x = 50, y = 500;
        for (int i = 0; i < 26; ++i) {
            keys[i] = ' ';
            keyRects[i] = sf::RectangleShape(sf::Vector2f(50, 50));
            keyRects[i].setPosition(x, y);
            keyRects[i].setOutlineThickness(2);
            keyRects[i].setOutlineColor(sf::Color::Black);

            x += 60; 
            if (i + 1 == 13) {
                x = 50;
                y += 60;
            }
        }
    }

    void updateKey(char key, char status) {
        int index = key - 'A';
        if (index >= 0 && index < 26) {
            if (keys[index] == ' ' || (keys[index] != 'G' && status != 'B'))
                keys[index] = status;
        }
    }

    void draw(sf::RenderWindow& window, const sf::Font& font) {
        for (int i = 0; i < 26; ++i) {
            sf::RectangleShape& key = keyRects[i];
            switch (keys[i]) {
            case 'G': key.setFillColor(sf::Color::Green); break;
            case 'Y': key.setFillColor(sf::Color::Yellow); break;
            case 'B': key.setFillColor(sf::Color(128, 128, 128)); break;
            default: key.setFillColor(sf::Color::White); break;
            }

            window.draw(key);

            sf::Text keyText;
            keyText.setFont(font);
            keyText.setString(string(1, 'A' + i));
            keyText.setCharacterSize(20);
            keyText.setFillColor(sf::Color::Black);
            keyText.setPosition(key.getPosition().x + 15, key.getPosition().y + 10);
            window.draw(keyText);
        }
    }

    char getKeyPressed(sf::Vector2f mousePos) {
        for (int i = 0; i < 26; ++i) {
            if (keyRects[i].getGlobalBounds().contains(mousePos)) {
                return 'A' + i;
            }
        }
        return '\0'; // in the case of no key clicked
    }
};
#endif