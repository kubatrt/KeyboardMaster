#include "ToggleKey.h"

namespace framework
{

ToggleKey::ToggleKey(sf::Keyboard::Key key)
:   m_key (key)
{ }

bool ToggleKey::isKeyPressed()
{
    if (delayTimer_.getElapsedTime().asSeconds() > 0.2)
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
