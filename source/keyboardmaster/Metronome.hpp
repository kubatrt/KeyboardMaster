#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "frameworkLib/Utilities.hpp"
#include "SoundPlayer.hpp"

namespace km
{

/**
 * \class Metronome
 * BPM - beats per minute
 * 	Example: 80 beats per 60 seconds
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

    void toggle();
    void start();
    void stop();
    void update(sf::Time deltaTime);

private:
    sf::Clock timer_;
    sf::Time elapsedTime_;
    const unsigned TickSeparator_ = 4;
    unsigned int bpm_;
    unsigned int tick_;
    bool isPlaying_;
};

}
