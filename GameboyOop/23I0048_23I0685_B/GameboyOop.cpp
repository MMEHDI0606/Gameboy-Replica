//#include <SFML/Graphics.hpp>
//#include<iostream>
//using namespace sf;
//using namespace std;
//int main() {
//    // Create a window with the title "SFML Test"
//    RenderWindow window(VideoMode(1000, 800), "GameBoy");
//
//    // Load a texture from a file
//    Texture texture;
//    if (!texture.loadFromFile("../Sprite/gb.png")) { // Replace "sprite.png" with your image file
//        cerr << "Error loading texture!" << endl;
//        return -1;
//    }
//
//    // Create a sprite and set its texture
//    Sprite gameboyicon;
//    gameboyicon.setTexture(texture);
//
//    gameboyicon.setScale(0.5f, 0.5f);
//    // Optionally set sprite position (centered in the window)
//    gameboyicon.setPosition(
//        Vector2f(220.0f,150.0f));
//    // Main game loop
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        // Clear the screen
//        window.clear();
//
//        // Draw the circle
//        window.draw(gameboyicon);
//
//        // Display the window
//        window.display();
//    }
//
//    return 0;
//}
