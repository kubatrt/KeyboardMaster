#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.hpp"
#include "../Util/NonCopyable.hpp"
#include "../Util/NonMoveable.hpp"


namespace framework
{

class ResourceHolder : public NonCopyable, public NonMovable
{
    public:
        static ResourceHolder& get();

        ResourceManager<sf::Font>           fonts;
        ResourceManager<sf::Texture>        textures;
        ResourceManager<sf::SoundBuffer>    sounds;

        // TODO
        // soundBuffer
        // Music
        // Shader

    private:
        ResourceHolder();
};

}
