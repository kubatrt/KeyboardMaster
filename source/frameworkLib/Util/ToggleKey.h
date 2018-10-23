#pragma once 

#include <SFML/Graphics.hpp>

namespace framework
{

class ToggleKey
{
    public:
        ToggleKey(sf::Keyboard::Key);

        bool isKeyPressed();

    private:
        sf::Keyboard::Key m_key;
        sf::Clock delayTimer_;

};

}
