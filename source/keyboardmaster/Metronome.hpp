#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "frameworkLib/Utilities.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

/**
 * \class Metronome TODO: finish this....
 * bpm - beats per minute
 * 	80 beats per 60 seconds
 *  tick interval = 60 / 80 = 0,75 s
 *
*/

class Metronome
{
public:
    Metronome() = delete;
	Metronome(unsigned int bpm);

    void setBPM(unsigned int bpm) { bpm_ = bpm; }
    unsigned int getBPM() const { return bpm_; }
    void start();
    void stop();
    void update(sf::Time deltaTime);

private:
    void playSound();

    const unsigned tickSeparator_ = 4;
    sf::Clock timer_;
    sf::Time elapsedTime_;
    unsigned int bpm_;
    unsigned int tick_;
    bool isPlaying_;
};

}
