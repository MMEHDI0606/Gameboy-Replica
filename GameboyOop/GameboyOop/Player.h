#ifndef PLAYER_H
#define PLAYER_H

#include "AchievementSystem.h"
#include <iostream>
#include <fstream>

using namespace std;

class Player {
private:
    char name[50];
    int highScores[3]; // For Snake, Wordle, Hangman
    AchievementSystem achievements1;

    // Helper function to copy a character array
    void copyName(const char* source, char* destination) {
        int i = 0;
        while (source[i] != '\0' && i < 49) {
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0'; 
    }

    // Helper function to zero out an integer array
    void zeroArray(int* arr, int size) {
        for (int i = 0; i < size; ++i) {
            arr[i] = 0;
        }
    }

public:
    Player() {  }
    Player(const char* playerName) {
        copyName(playerName, name);
        zeroArray(highScores, 3);
    }

    const char* getName() const { return name; }

    inline void updateHighScore(int gameIndex, int score) {
        if (score > highScores[gameIndex]) {
            highScores[gameIndex] = score;
        }
    }

    inline int getHighScore(int gameIndex) const { return highScores[gameIndex]; }
    AchievementSystem& getAchievements() { return achievements1; }

    void checkAchievements(const Player& player) {
        if (player.getHighScore(0) >= 50) { // Snake Game: 5 foods eaten so score would be 50
            getAchievements().unlockAchievement(0);
        }
        if (player.getHighScore(1) == 1) { // Wordle
            getAchievements().unlockAchievement(1);
        }
        if (player.getHighScore(2) >= 5) { // Hangman
            getAchievements().unlockAchievement(2);
        }
    }

    inline void saveProgress( ) {
        ofstream file("player_progress.txt");
        if (file.is_open()) {
            file << name << endl;
            for (int i = 0; i < 3; ++i) {
                file << highScores[i] << endl;
            }
            for (int i = 0; i < 3; ++i) {
                file << achievements1.achievements[i].unlocked << endl;
            }
        }
        file.close();
    }

    inline void loadProgress() {
        ifstream file("player_progress.txt");
        if (file.is_open()) {
            file >> name;
            for (int i = 0; i < 3; ++i) {
                file >> highScores[i];
            }
            for (int i = 0; i < 3; ++i) {
                file >> achievements1.achievements[i].unlocked;
            }
        }
        file.close();
    }
};

#endif // PLAYER_H
