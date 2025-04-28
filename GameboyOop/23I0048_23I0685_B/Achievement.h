#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <iostream>

using namespace std;

class Achievement {
public:
    Achievement();
    Achievement(const char* title, const char* description, bool completed);
    void markAsCompleted();
    bool isCompleted() const;
    void displayAchievement() const;

private:
    char title[50]; // Title of the achievement
    char description[100]; // Description of the achievement
    bool completed; // Status of the achievement
};

#endif