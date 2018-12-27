#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "frameworkLib/Utilities.hpp"

/* Metronome TODO: finish this....
    BPM - beats per minute
    80 beats per 60 seconds
    interval = 60 / 80 = 0,75 s
*/
class Metronome
{
public:
    Metronome(unsigned int bpm)
		: bpm_(bpm)
		, isPlaying_(false)
		, tick_(0)
    {
    }

    void setBPM(unsigned int bpm) { bpm_ = bpm; }
    unsigned int getBPM() const { return bpm_; }

    void start() 
    {
        timer_.restart();
        isPlaying_ = true;
        tick_ = 0;
    }

    void stop() 
    {
        elapsedTime_ = timer_.restart();
        isPlaying_ = false;
    }

    void update(sf::Time deltaTime)
    {
        if(!isPlaying_)
            return;

        elapsedTime_ = timer_.getElapsedTime();
        sf::Time interval = sf::seconds(60.f) / sf::seconds(bpm_);
        if (elapsedTime_ >= interval)
        {
            elapsedTime_ = sf::Time::Zero;
            playSound();
        }

    }

private:

    void playSound()
    {
    	tick_++;
    	if(tick_ % 4)
    	{

    	}
    	else
    	{

    	}
    };

    sf::Clock timer_;
    sf::Time elapsedTime_;
    unsigned int bpm_;
    unsigned int tick_;
    bool isPlaying_;
};
