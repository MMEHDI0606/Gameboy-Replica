#include "SnakeGame.h"

SnakeGame::SnakeGame() {
    // Initialize snake starting position and grid
    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random food generation
    snakeBody[0][0] = gridWidth / 2; // X position of head
    snakeBody[0][1] = gridHeight / 2; // Y position of head
    direction = Game::Direction::RIGHT;  // Correctly using the scoped Direction
    snakeLength = 5; // Initial length
    food[0] = rand() % (gridWidth-1); // X position of food
    food[1] = rand() % (gridHeight-1); // Y position of food
    score = 0; // Initial score
    speed = 200; // Initial speed in milliseconds
    isGameOver = false;

    // Load textures
    if (!headTexture.loadFromFile("head.png") ||
        !bodyTexture.loadFromFile("body.png") ||
        !tailTexture.loadFromFile("tail.png") ||
        !foodTexture.loadFromFile("fruit.png") ||
        !wallTexture.loadFromFile("walls.png")) {
        std::cerr << "Failed to load textures!" << std::endl;
        return;
    }

    headSprite.setTexture(headTexture);
    bodySprite.setTexture(bodyTexture);
    tailSprite.setTexture(tailTexture);
    foodSprite.setTexture(foodTexture);
    wallSprite.setTexture(wallTexture);

    headSprite.setScale(.0625, .0625);
    bodySprite.setScale(.0625, .0625);
    tailSprite.setScale(.0625, .0625);
    foodSprite.setScale(.0625, .0625);
    wallSprite.setScale(.256, .2);

    // Load background texture
    if (!backgroundTexture.loadFromFile("snake.jpg")) {
        cout << "Failed to load background texture!" << endl;
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(8, 8);
    // Load font for score display
    if (!font.loadFromFile("b2.ttf")) {            //MEHDIIIIIIIIIII - REPLACE WITH WTC FONT U HAVE
        cout << "Failed to load font!" << endl;
        return;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::Red);                //I TEMPORARILY CHANGED THE COLOR CUZ WO BLACK BACKGROUND PY NAZAR NHI AA RAHA THA
    
    // Load Game Over texture
    if (!gameOverTexture.loadFromFile("gameover.png")) {
        std::cout << "Failed to load Game Over texture!" << std::endl;
    }
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(300, 200); // Center position
}


bool SnakeGame::getIsGameOver() const {
    return isGameOver;
}

// Start the Snake game
void SnakeGame::startGame() {
    cout << "Starting Snake Game..." << endl;
    window.create(VideoMode(1000, 600), "Snake Game");

}

// End the Snake game
void SnakeGame::endGame() {
    cout << "Ending Snake Game..." << endl;
    isGameOver = true;
    window.close();
}

// Render the game elements
void SnakeGame::render() {
    if (!window.isOpen()) {
        std::cerr << "Window is not open!" << std::endl;
        return;
    }

    window.clear();

    if (isGameOver) {
        // Display Game Over screen
        window.draw(gameOverSprite);
        window.display();
        return;
    }

    // Draw the background
    window.draw(backgroundSprite);

    // Draw walls
    for (int i = 0; i < gridWidth; ++i) {
        wallSprite.setPosition(i * 20, 0);
        window.draw(wallSprite);
        wallSprite.setPosition(i * 20, (gridHeight - 1) * 20);
        window.draw(wallSprite);
    }
    for (int i = 0; i < gridHeight; ++i) {
        wallSprite.setPosition(0, i * 20);
        window.draw(wallSprite);
        wallSprite.setPosition((gridWidth - 1) * 20, i * 20);
        window.draw(wallSprite);
    }


    // Draw the snake
    for (int i = 0; i < snakeLength; ++i) {
        if (i == 0) {
            headSprite.setPosition(snakeBody[i][0] * 20, snakeBody[i][1] * 20);
            window.draw(headSprite);
        }
        else if (i == snakeLength - 1) {
            tailSprite.setPosition(snakeBody[i][0] * 20, snakeBody[i][1] * 20);
            window.draw(tailSprite);
        }
        else {
            bodySprite.setPosition(snakeBody[i][0] * 20, snakeBody[i][1] * 20);
            window.draw(bodySprite);
        }
    }

    // Draw the food
    foodSprite.setPosition(food[0] * 20, food[1] * 20);
    window.draw(foodSprite);

    // Display the score
    stringstream ss;
    ss << "Score: " << score;
    scoreText.setString(ss.str());
    scoreText.setPosition(900, 20);
    window.draw(scoreText);

    window.display();
}

// Handle the snake movement
void SnakeGame::moveSnake() {
    // Move the body (from tail to head)
    for (int i = snakeLength - 1; i > 0; --i) {
        snakeBody[i][0] = snakeBody[i - 1][0];
        snakeBody[i][1] = snakeBody[i - 1][1];
    }

    // Update the head based on direction
    switch (direction) {
    case Game::Direction::UP:
        snakeBody[0][1] -= 1;
        break;
    case Game::Direction::DOWN:
        snakeBody[0][1] += 1;
        break;
    case Game::Direction::LEFT:
        snakeBody[0][0] -= 1;
        break;
    case Game::Direction::RIGHT:
        snakeBody[0][0] += 1;
        break;
    }

    detectCollision();
}

// Detect collisions for the snake
void SnakeGame::detectCollision() {

    if (!isGameOver) {
        // Handle collisions with the wall
        if (snakeBody[0][0] <= 0 || snakeBody[0][0] >= gridWidth - 1 || snakeBody[0][1] <= 0 || snakeBody[0][1] >= gridHeight - 1) {
            cout << "Game Over: Collision with wall!" << endl;
            endGame();
        }

        // Handle collisions with itself
        for (int i = 1; i < snakeLength; ++i) {
            if (snakeBody[0][0] == snakeBody[i][0] && snakeBody[0][1] == snakeBody[i][1]) {
                cout << "Game Over: Collision with self!" << endl;
                endGame();
            }
        }

        // Handle eating food
        if (snakeBody[0][0] == food[0] && snakeBody[0][1] == food[1]) {
            snakeLength++;
            food[0] = rand() % (gridWidth - 2) + 1;
            food[1] = rand() % (gridHeight - 2) + 1;
            score += 10;

            // Increase difficulty if score reaches 50
            if (score % 50 == 0) {
                increaseDifficulty();
            }
        }
    }
}

// Increase the difficulty by making the snake move faster
void SnakeGame::increaseDifficulty() {
    if (speed > 50) { // Ensure the speed doesn't go too fast
        speed -= 20;
        cout << "Increasing difficulty. New speed: " << speed << "ms" << endl;
    }
}

// If Direction is scoped in the Game class:
void SnakeGame::updateDirection(Game::Direction newDirection) {
    // Prevent reversing direction
    if ((direction == Game::Direction::UP && newDirection != Game::Direction::DOWN) ||
        (direction == Game::Direction::DOWN && newDirection != Game::Direction::UP) ||
        (direction == Game::Direction::LEFT && newDirection != Game::Direction::RIGHT) ||
        (direction == Game::Direction::RIGHT && newDirection != Game::Direction::LEFT)) {
        direction = newDirection;
    }
}

void SnakeGame::saveGameState(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Failed to save game state!" << endl;
        return;
    }

    outFile << "SnakeLength " << snakeLength << "\n";
    outFile << "SnakeBody ";
    for (int i = 0; i < snakeLength; ++i) {
        outFile << snakeBody[i][0] << " " << snakeBody[i][1] << " ";
    }
    outFile << "\n";
    outFile << "Food " << food[0] << " " << food[1] << "\n";
    outFile << "Score " << score << "\n";
    outFile << "Speed " << speed << "\n";
    outFile << "Direction " << static_cast<int>(direction) << "\n";

    outFile.close();
    cout << "Game state saved successfully!" << endl;
}

void SnakeGame::loadGameState(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Failed to load game state!" << endl;
        return;
    }

    // Read and restore game data
    string label;

    inFile >> label >> snakeLength;
    if (label != "SnakeLength") {
        cout << "Corrupted file: Missing SnakeLength!" << endl;
        return;
    }

    inFile >> label;
    if (label != "SnakeBody") {
        cout << "Corrupted file: Missing SnakeBody!" << endl;
        return;
    }
    for (int i = 0; i < snakeLength; ++i) {
        inFile >> snakeBody[i][0] >> snakeBody[i][1];
    }

    inFile >> label >> food[0] >> food[1];
    if (label != "Food") {
        cout << "Corrupted file: Missing Food!" << endl;
        return;
    }

    inFile >> label >> score;
    if (label != "Score") {
        cout << "Corrupted file: Missing Score!" << endl;
        return;
    }

    inFile >> label >> speed;
    if (label != "Speed") {
        cout << "Corrupted file: Missing Speed!" << endl;
        return;
    }

    int dir;
    inFile >> label >> dir;
    if (label != "Direction") {
        cout << "Corrupted file: Missing Direction!" << endl;
        return;
    }
    direction = static_cast<Game::Direction>(dir);

    inFile.close();
    cout << "Game state loaded successfully!" << endl;
}

void SnakeGame::handlePauseResume() {
    static bool isPaused = false; // Tracks pause state
    isPaused = !isPaused;
    if (isPaused) {
        saveGameState("game_state.txt");
        std::cout << "SnakeGame paused. State saved.\n";
    }
    else {
        loadGameState("game_state.txt");
        std::cout << "SnakeGame resumed. State loaded.\n";
    }
}
//int main() {
//    SnakeGame game;
//    game.startGame();
//
//    while (game.speed > 0) { // Ensures the game continues until speed becomes 0 or the window is closed
//        game.render();
//        game.moveSnake();
//
//        // Add delay for game speed control
//        sf::sleep(milliseconds(game.speed));
//
//        // Handle keyboard input
//        if (Keyboard::isKeyPressed(Keyboard::Up)) {
//            game.updateDirection(UP);
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
//            game.updateDirection(DOWN);
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
//            game.updateDirection(LEFT);
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
//            game.updateDirection(RIGHT);
//        }
//    }
//
//    return 0;
//}
