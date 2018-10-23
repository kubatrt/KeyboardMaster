#pragma once

#include <SFML\System.hpp>
#include <functional>

namespace km
{

class Scheduler
{
public:
    Scheduler(sf::Time treshold, std::function<void()> callback)
        : treshold_(treshold)
        , callback_(callback)
        , done_(false)
        , started_(false)
    {
    }

    bool isStarted() const { return started_; }
    bool isDone() const { return done_; }

    void start()
    {
        started_ = true;
        done_ = false;
        timer_.restart();
    }

    void update()
    {
        if(done_ || !started_) 
            return;

        if (timer_.getElapsedTime() >= treshold_)
        {
            done_ = true;
            callback_();
        }
    }

private:
    sf::Time treshold_;
    sf::Clock timer_;
    std::function<void()> callback_;
    bool done_;
    bool started_;
};

}