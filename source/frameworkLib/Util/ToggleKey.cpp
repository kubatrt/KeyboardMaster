#include "ToggleKey.h"

namespace framework
{

constexpr float TOGGLE_KEY_TIME {0.2f};

ToggleKey::ToggleKey(sf::Keyboard::Key key)
:   m_key (key)
{ }

bool ToggleKey::isKeyPressed()
{
    if (delayTimer_.getElapsedTime().asSeconds() > TOGGLE_KEY_TIME)
    {
        if (sf::Keyboard::isKeyPressed(m_key))
        {
            delayTimer_.restart();
            return true;
        }
    }
    return false;
}

}
