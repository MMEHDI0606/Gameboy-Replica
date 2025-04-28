#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>
#include "ali.h" // Include the flight booking logic

// Structure to hold city information
struct City {
    std::string name;
    float x, y; // Coordinates on the globe
};

// Function to draw a line between two points
void drawLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, sf::Color color) {
    sf::Vertex line[] = {
        sf::Vertex(start, color),
        sf::Vertex(end, color)
    };
    window.draw(line, 2, sf::Lines);
}

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flight Graph Visualization");

    // Load the background image
    sf::Texture globeTexture;
    if (!globeTexture.loadFromFile("bck.jpg")) {
        std::cerr << "Error loading background image!" << std::endl;
        return -1;
    }
    sf::Sprite globeSprite(globeTexture);
    globeSprite.setScale(0.7f, 0.7f);

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("Komika.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Define city locations on the globe
    std::map<std::string, City> cities = {
        {"New York", {"New York", 300, 150}},
        {"London", {"London", 400, 120}},
        {"Paris", {"Paris", 420, 140}},
        {"Tokyo", {"Tokyo", 700, 200}},
        {"Sydney", {"Sydney", 750, 400}},
        {"Singapore", {"Singapore", 600, 350}},
        {"Hong Kong", {"Hong Kong", 650, 250}},
        {"Seoul", {"Seoul", 680, 180}},
        {"Berlin", {"Berlin", 430, 110}},
        {"Amsterdam", {"Amsterdam", 410, 125}},
        {"Islamabad", {"Islamabad", 550, 210}}
    };

    // Initialize the flight graph and load data
    Graph flightGraph(11);
    flightGraph.addCity("HotelCharges_perday.txt");
    flightGraph.addEdgesFromFile("Flights.txt");

    // Gather booked paths from user input
    std::vector<std::pair<std::string, std::string>> bookedPaths;
    std::cout << "Enter origin city: ";
    std::string origin;
    std::cin >> origin;
    std::cout << "Enter destination city: ";
    std::string destination;
    std::cin >> destination;

    const int maxPaths = 100;
    Edge* allPaths[maxPaths][10] = { nullptr };
    int pathCounts[maxPaths] = { 0 };
    int totalPaths = 0;

    flightGraph.BookingAllPathFlightsFinder(origin, destination, allPaths, pathCounts, totalPaths);

    if (totalPaths > 0) {
        std::cout << "Available flight paths:" << std::endl;
        for (int i = 0; i < totalPaths; i++) {
            for (int j = 0; j < pathCounts[i] - 1; j++) {
                std::string cityA = flightGraph.cities[flightGraph.findCityIndex(allPaths[i][j]->airline)];
                std::string cityB = flightGraph.cities[flightGraph.findCityIndex(allPaths[i][j + 1]->airline)];
                bookedPaths.emplace_back(cityA, cityB);
            }
        }
    }
    else {
        std::cout << "No paths available." << std::endl;
        return 0;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw the background globe
        window.draw(globeSprite);

        // Draw the city nodes and labels
        for (const auto& [name, city] : cities) {
            sf::CircleShape circle(5);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(city.x - circle.getRadius(), city.y - circle.getRadius());
            window.draw(circle);

            sf::Text label(name, font, 12);
            label.setPosition(city.x + 10, city.y - 10);
            label.setFillColor(sf::Color::White);
            window.draw(label);
        }

        // Draw the booked flight paths
        for (const auto& path : bookedPaths) {
            const auto& cityA = cities[path.first];
            const auto& cityB = cities[path.second];
            drawLine(window, sf::Vector2f(cityA.x, cityA.y), sf::Vector2f(cityB.x, cityB.y), sf::Color::Blue);
        }

        window.display();
    }

    return 0;
}
