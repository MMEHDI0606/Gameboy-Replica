#ifndef HANGMANFIGURE_H
#define HANGMANFIGURE_H

#include <SFML/Graphics.hpp>

class HangmanFigure {
public:
    void draw(sf::RenderWindow& window, int lives) const {
        // Base 
        sf::RectangleShape pole(sf::Vector2f(10, 300));
        pole.setFillColor(sf::Color::Black);
        pole.setPosition(100, 50);

        sf::RectangleShape beam(sf::Vector2f(150, 10));
        beam.setFillColor(sf::Color::Black);
        beam.setPosition(100, 50);

        sf::RectangleShape rope(sf::Vector2f(5, 50));
        rope.setFillColor(sf::Color::Black);
        rope.setPosition(250, 50);

        window.draw(pole);
        window.draw(beam);
        window.draw(rope);

        // Draw parts of the figure based on remaining lives
        if (lives <= 5) { // Head
            sf::CircleShape head(25);
            head.setFillColor(sf::Color::Transparent);
            head.setOutlineColor(sf::Color::Black);
            head.setOutlineThickness(5);
            head.setPosition(225, 100);
            window.draw(head);
        }

        if (lives <= 4) { // Body
            sf::RectangleShape body(sf::Vector2f(10, 100));
            body.setFillColor(sf::Color::Black);
            body.setPosition(245, 150);
            window.draw(body);
        }

        if (lives <= 3) { // Left Arm
            sf::RectangleShape leftArm(sf::Vector2f(70, 10));
            leftArm.setFillColor(sf::Color::Black);
            leftArm.setPosition(195, 207);
            leftArm.setRotation(-45);
            window.draw(leftArm);
        }

        if (lives <= 2) { // Right Arm
            sf::RectangleShape rightArm(sf::Vector2f(70, 10));
            rightArm.setFillColor(sf::Color::Black);
            rightArm.setPosition(252, 153);
            rightArm.setRotation(45);
            window.draw(rightArm);
        }

        if (lives <= 1) { // This is actually the Right Leg
            sf::RectangleShape leftLeg(sf::Vector2f(70, 10));
            leftLeg.setFillColor(sf::Color::Black);
            leftLeg.setPosition(256, 242);
            leftLeg.setRotation(45);
            window.draw(leftLeg);
        }

        if (lives <= 0) { // nd this is actually the Left Leg
            sf::RectangleShape rightLeg(sf::Vector2f(70, 10));
            rightLeg.setFillColor(sf::Color::Black);
            rightLeg.setPosition(200, 283);
            rightLeg.setRotation(-45);
            window.draw(rightLeg);
        }
    }
};
#endif
