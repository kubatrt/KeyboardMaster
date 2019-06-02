#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.hpp"


namespace framework
{

// Global resource holder
// Example usage:
//	font_ = fw::ResourceHolder::get().fonts.get("CourierNew");
//
class ResourceHolder
{
    public:
		~ResourceHolder() = default;
		ResourceHolder(const ResourceHolder&) = delete;
		ResourceHolder(ResourceHolder&&) = delete;
		ResourceHolder& operator=(const ResourceHolder&) = delete;
		ResourceHolder& operator=(ResourceHolder&&) = delete;

        static ResourceHolder& get();

        ResourceManager<sf::Font>           fonts;
        ResourceManager<sf::Texture>        textures;
        ResourceManager<sf::SoundBuffer>    sounds;

    private:
        ResourceHolder();
};

}
