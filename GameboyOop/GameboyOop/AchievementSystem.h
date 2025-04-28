#ifndef ACHIEVEMENTSYSTEM_H
#define ACHIEVEMENTSYSTEM_H

#include <iostream>
using namespace std;

class AchievementSystem {
private:
    
    void setName(char* destination, const char* source) {
        int i = 0;
        while (source[i] != '\0' && i < 49) { 
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0'; 
    }

public:
    struct Achievement {
        char name[50];
        bool unlocked;
    } achievements[3];


    AchievementSystem() {
        setName(achievements[0].name, "Snake Master (5 foods eaten without dying)");
        setName(achievements[1].name, "Wordle Wizard (Word guessed on first try)");
        setName(achievements[2].name, "Hangman Hero (5 wins streak)");
        for (int i = 0; i < 3; ++i) {
            achievements[i].unlocked = false;
        }
    }

    void unlockAchievement(int index) {
        if (index >= 0 && index < 3) {
            achievements[index].unlocked = true;
        }
    }

    void displayAchievements() const {
        cout << "Achievements:" << endl;
        for (int i = 0; i < 3; ++i) {
            cout << achievements[i].name << " - " << (achievements[i].unlocked ? "Unlocked" : "Locked") << endl;
        }
    }
};
#endif
