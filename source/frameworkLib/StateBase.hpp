#pragma once

#include <memory>
#include <SFML/Graphics.hpp>


namespace framework
{

class GameBase;

class StateBase
{
public:
    StateBase(GameBase& game)
    : game_(game)
    {
    }
    virtual ~StateBase() = default;
    StateBase(const StateBase&) = delete;
    const StateBase& operator=(const StateBase&) = delete;

    virtual void handleEvents(sf::Event e) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;

    /*void OnEnter();
    void OnPause();
    void OnResume();
    void OnExit();*/

protected:
    GameBase& game_;
};
using StateBasePtr = std::unique_ptr<StateBase> ;
using StateBaseSPtr = std::shared_ptr<StateBase>;

}
