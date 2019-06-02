#pragma once

#include <iostream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "StateBase.hpp"
#include "IGameComponent.hpp"

namespace framework
{

// Base class for implementation of the game (as an application). Runs main game loop, window handling and state management.
// Implementation of game logic should be written using StateBase class. At least one state required to run, otherwise throws exception.
// Components added at this level applies to whole game <currently>.
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
    GameBase(GameBase&&) = delete;
    GameBase& operator=(const GameBase&) = delete;
    GameBase&& operator=(GameBase&&) = delete;

    // TOP interface. This should be defined elsewhere? outside this class. I can call in any state the public method run(). Do not do this!
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

            // Update game logic
            update(elapsed);
            for(auto& c : components_) { c->update(elapsed); }

            window_.clear();
            draw(window_);
            for(auto& c : components_) { c->draw(window_); }

            window_.display();

            handleEvents();
            tryPop();
        }
        return 0;
    }

    template<typename T, typename... Args>
    void addComponent(Args&&... args)
    {
    	components_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    /////////////////////////////////////////////
    // State management
    ////////////////////////////////////////////

    template<typename T, typename... Args>
    void pushState(Args&&... args)
    {
        states_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    };

    void popState()
    {
        popState_ = true;
    };


    const sf::RenderWindow& getWindow() const
    {
    	return window_;
    };

    void createWindow()
    {
        auto style = isFullscreen_ ? sf::Style::Fullscreen : sf::Style::Default;
        window_.create({windowWidth_, windowHeight_}, windowTitle_, style);
    }

    void closeWindow()
    {
    	window_.close();
    }

    void quit()
    {
    	states_.clear();
    }

    void toggleFullscreen()
    {
        isFullscreen_ = !isFullscreen_;
        closeWindow();
        createWindow();
    }

protected:
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
    virtual void handleEvents() = 0;

    StateBase& getCurrentState()
    {
        // At least one state required - what if there is no any? throw exception? or can be null? maybe use pointer instead!
        assert(states_.size()); // give up with assertions... ~Mayers
        return *states_.back();
    };

    // Removing last state from the stack means quit!
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
    std::vector<GameComponentPtr> components_;

    bool popState_;
    bool isFullscreen_;
    std::string windowTitle_;
    sf::Uint32 windowWidth_;
    sf::Uint32 windowHeight_;
};


}   // framework
