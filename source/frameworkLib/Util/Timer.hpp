#pragma once

#include <SFML/System/Clock.hpp>

namespace framework
{

// TODO: Not tested yet
class Timer
{
private:
	enum { Stopped, Running, Paused } state_;
	sf::Time time_;
	sf::Clock clock_;

public:

Timer(sf::Time initialTime = sf::Time::Zero)
{
	reset();
	add(initialTime);
}

sf::Time add(sf::Time time)
{
	time_ += time;

	if(state_ == Stopped)
		state_ = Paused;

	return getElapsedTime();
}

sf::Time reset(bool start = false)
{
	sf::Time time = getElapsedTime();
	time_ = sf::Time::Zero;
	state_ = Stopped;

	if(start)
		resume();

	return time_;
}

sf::Time pause()
{
	if(isRunning())
	{
		state_ = Paused;
		time_ += clock_.getElapsedTime();
	}
	return getElapsedTime();
}

bool isRunning() const
{
	return state_ == Running;
}

sf::Time toggle()
{
	if(isRunning())
		pause();
	else
		resume();

	return getElapsedTime();
}

sf::Time resume()
{
   if (!isRunning())
   {
	   state_ = Running;
	   clock_.restart();
   }
   return getElapsedTime();
}

sf::Time getElapsedTime() const
{
	switch(state_)
	{
	case Stopped:
		return sf::Time::Zero;
	case Running:
		return time_ + clock_.getElapsedTime();
	case Paused:
		return time_;
	}
	return sf::Time::Zero;
}

// implicit conversion to sf::Time
operator sf::Time() const
{
	return getElapsedTime();
}

};

}
