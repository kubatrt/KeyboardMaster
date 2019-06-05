#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.hpp"


namespace framework
{

// Global resource holder
// Example usage:
//	font_ = fw::ResourceHolder::get().fonts.get("CourierNew");
//  texture_ = fw::ReosurceHolder::get().sounds.get("texture");
//	sound = fw::ReosurceHolder::get().sounds.get("shoot");

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
