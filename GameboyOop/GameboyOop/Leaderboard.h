#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Player.h"
#include <iostream>

using namespace std;

class Leaderboard {
private:
    struct Score {
        char playerName[50];
        int score;
    } highScores[10];

    // Helper function to copy a character array
    void copyName(const char* source, char* destination) {
        int i = 0;
        while (source[i] != '\0' && i < 49) {
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0'; // Null-terminate the destination string
    }

public:
    Leaderboard() {
        for (int i = 0; i < 10; ++i) {
            highScores[i].score = 0;
            highScores[i].playerName[0] = '\0'; // Initialize playerName as an empty string
        }
    }

    // Update the leaderboard with the player's score
    void updateScore(const Player& player, int score) {
        for (int i = 0; i < 10; ++i) {
            if (score > highScores[i].score) {
                // Shift lower scores down the list
                for (int j = 9; j > i; --j) {
                    highScores[j] = highScores[j - 1];
                }
                // Insert new high score
                highScores[i].score = score;
                copyName(player.getName(), highScores[i].playerName);
                break;
            }
        }
    }

    void displayTopScores() const {
        cout << "Leaderboard:\n";
        for (int i = 0; i < 10; ++i) {
            if (highScores[i].score > 0) {
                cout << highScores[i].playerName << ": " << highScores[i].score << endl;
            }
        }
    }
};

#endif // LEADERBOARD_H
