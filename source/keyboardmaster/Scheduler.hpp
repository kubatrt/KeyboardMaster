#pragma once

#include <SFML/System.hpp>
#include <functional>

namespace km
{

// Simple event scheduler
class Scheduler
{
public:
    Scheduler(sf::Time treshold, std::function<void()> callback = nullptr)
        : treshold_(treshold)
        , callback_(callback)
        , done_(false)
        , started_(false)
    {
    	LOG_DEBUG("Scheduler CTOR tresh:" << treshold.asSeconds() );
    }

    Scheduler& setCallback(std::function<void()> callback) { callback_ = callback; return *this; }
    void setTreshold(const sf::Time treshold) { treshold_ = treshold; }
    bool isStarted() const { return started_; }
    bool isDone() const { return done_; }

    void reset()
    {
    	started_= false;
    	done_ = false;
    }

    void restart()
    {
    	reset();
    	start();
    }

    void start()
    {
        started_ = true;
        timer_.restart();
        LOG_DEBUG("Scheduler start");
    }

    void update()
    {
        if(done_ || !started_) 
            return;

        if (timer_.getElapsedTime() >= treshold_)
        {
        	LOG_DEBUG("Scheduler callback() " << timer_.getElapsedTime().asSeconds());
            done_ = true;
            callback_();
        }
    }

private:
    sf::Time treshold_;
    sf::Clock timer_; // not required?
    std::function<void()> callback_;
    bool done_;
    bool started_;
};

}
