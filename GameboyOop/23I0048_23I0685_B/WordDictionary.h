#ifndef WORDDICTIONARY_H
#define WORDDICTIONARY_H
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class WordDictionary {
private:
    const static int MAX_WORDS = 100;
    const static int WORD_LENGTH = 6; // 5+1 for null terminator
    char words[MAX_WORDS][WORD_LENGTH];
    int wordCount;

    void copyString(char* dest, const char* src, int length) const {
        for (int i = 0; i < length - 1; ++i) {
            if (src[i] == '\0') break;
            dest[i] = src[i];
        }
        dest[length - 1] = '\0'; 
    }

    bool compareStrings(const char* str1, const char* str2) const {
        for (int i = 0; i < WORD_LENGTH; ++i) {
            char c1 = (str1[i] >= 'a' && str1[i] <= 'z') ? str1[i] - ('a' - 'A') : str1[i];
            char c2 = (str2[i] >= 'a' && str2[i] <= 'z') ? str2[i] - ('a' - 'A') : str2[i];

            if (c1 != c2) return false;
            if (c1 == '\0') break; 
        }
        return true;
    }


public:
    WordDictionary() : wordCount(14) {
        const char defaultWords[14][WORD_LENGTH] = {"MAHAM", "BRAIN", "CHESS", "KNIFE", "SWORD", "FLAME", "SHOOK", "STAIN", "WORDY", "PLANT", "ABIDE", "ABODE", "LEMON", "LARGE"};//GOTTA ADD MORE WORDSSSSSSSSSSSSSSSSSSSSSS
        for (int i = 0; i < wordCount; i++) {
            copyString(words[i], defaultWords[i], WORD_LENGTH);
        }
    }

    bool validateWord(const char* word) const {
        for (int i = 0; i < wordCount; i++) {
            if (compareStrings(words[i], word)) {
                return true;
            }
        }
        cout << "Invalid word: " << word << endl; 
        return false;
    }
};
#endif