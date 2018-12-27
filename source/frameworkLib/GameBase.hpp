#pragma once

#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "StateBase.hpp"
#include "IGameComponent.hpp"

namespace framework
{

class GameBase
{
public:
    GameBase(sf::Vector2u windowSize, std::string windowTitle)
        : window_(sf::VideoMode(windowSize.x, windowSize.y), windowTitle)
        , windowWidth_(windowSize.x)
        , windowHeight_(windowSize.y)
        , windowTitle_(windowTitle)
        , popState_(false)
        , isFullscreen_(false)
    {
    }
    virtual ~GameBase() = default;
    GameBase(const GameBase&) = delete;
    const GameBase& operator=(const GameBase&) = delete;
    GameBase(GameBase&&) = delete;
    GameBase&& operator=(GameBase&&) = delete;

    // TOP interface. This should be defined elsewhere, outside this class. I can call in any state it's public method run()
    // Main game loop
    int run()
    {
        sf::Clock timer;
        auto lastTime = sf::Time::Zero;

        while (window_.isOpen())
        {
            auto time = timer.getElapsedTime();
            auto elapsed = time - lastTime;
            lastTime = time;

            update(elapsed);
            draw(window_);
            handleEvents();

            tryPop();
        }
        return 0;
    }

    // In-state access, State management: get access within states implementation
    template<typename T, typename... Args>
    void pushState(Args&&... args)
    {
        states_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    };

    void popState()
    {
        popState_ = true;
    };

    const sf::RenderWindow& getWindow() const
    {
    	return window_;
    };

    void close()
    {
    	window_.close();
    }

    void create()
    {
        auto style = isFullscreen_ ? sf::Style::Fullscreen : sf::Style::Default;
        window_.create({windowWidth_, windowHeight_}, windowTitle_, style);
    }

    void toggleFullscreen()
    {
        isFullscreen_ = !isFullscreen_;
        close();
        create();
    }

protected:
    // These methods define an interface, should not be called within a state
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
    virtual void handleEvents() = 0;

    StateBase& getCurrentState()
    {
        // At least one state required - what if there is no any? throw exception? or can be null? use pointer instead!
        assert(states_.size()); // give up with assertions... ~Mayers
        return *states_.back(); // return reference
    };

    // Removing last state from the stack means exit from application
    void tryPop()
    {
        if (popState_)
        {
            states_.pop_back();
        }
        popState_ = false;
    };

    sf::RenderWindow window_;

private:
    std::vector<StateBasePtr> states_;
    //std::vector<IGameComponent> components_;

    bool popState_;
    bool isFullscreen_;
    std::string windowTitle_;
    sf::Uint32 windowWidth_;
    sf::Uint32 windowHeight_;
};


}   // framework
