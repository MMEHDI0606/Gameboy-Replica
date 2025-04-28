#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class SoundSystem {
public:
    SoundSystem();
    void playMusic(const string& filePath, bool loop = false);
    void stopMusic();
    void adjustVolume(int level);

private:
    int volume; // Volume level (0-100)
    Music music; // Use sf::Music for streaming audio
};

inline SoundSystem::SoundSystem() {
    volume = 10; // Default volume set to maximum
}

inline void SoundSystem::playMusic(const string& filePath, bool loop) {
    if (!music.openFromFile(filePath)) {
        cerr << "Failed to load music from " << filePath << endl;
        return;
    }
    music.setVolume(static_cast<float>(volume)); // Set the current volume
    music.setLoop(loop); // Enable or disable looping
    music.play(); // Start playing the music
    cout << "Playing music from: " << filePath << " (Looping: " << (loop ? "Enabled" : "Disabled") << ")" << endl;
}

inline void SoundSystem::stopMusic() {
    music.stop(); // Stop the currently playing music
    cout << "Music stopped." << endl;
}

inline void SoundSystem::adjustVolume(int level) {
    if (level < 0) level = 0;
    if (level > 100) level = 100; // Clamp volume level between 0 and 100
    volume = level; // Update the volume variable
    music.setVolume(static_cast<float>(volume)); // Apply the new volume
    cout << "Volume adjusted to: " << volume << "%" << endl;
}

#endif // SOUNDSYSTEM_H
