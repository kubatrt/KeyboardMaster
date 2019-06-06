#include "Metronome.hpp"

namespace km
{

Metronome::Metronome(unsigned int bpm)
	: bpm_(bpm)
	, isPlaying_(false)
	, tick_(0)
{
	LOG_DEBUG("Metronome CTOR bpm: " << bpm_);
}

void Metronome::toggle()
{
	if(isPlaying_)
		stop();
	else
		start();
}

void Metronome::start()
{
	timer_.restart();
	isPlaying_ = true;
	tick_ = 0;
	LOG_DEBUG("Metronome start: " << bpm_);
}

void Metronome::stop()
{
	elapsedTime_ = timer_.restart();
	isPlaying_ = false;
	LOG_DEBUG("Metronome stop");
}

void Metronome::update(sf::Time deltaTime)
{
	if(!isPlaying_)
		return;

	elapsedTime_ = timer_.getElapsedTime();
	sf::Time interval(sf::seconds(60.f / bpm_));
	if (elapsedTime_ >= interval)
	{
		elapsedTime_ = timer_.restart();
		tick_++;
		if(tick_ % TickSeparator_)
		{
			SoundPlayer::get().play("metro_beat");
		}
		else
		{
			SoundPlayer::get().play("metro_bar");
			tick_ = 0;
		}
	}

}

}
