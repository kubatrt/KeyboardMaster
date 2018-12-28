#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"

namespace framework
{


class SoundPlayer
{
public:
	~SoundPlayer() = default;
	SoundPlayer(const ResourceHolder&) = delete;
	SoundPlayer(ResourceHolder&&) = delete;
	SoundPlayer& operator=(const SoundPlayer&) = delete;
	SoundPlayer& operator=(SoundPlayer&&) = delete;

	static SoundPlayer& get()
	{
	    static SoundPlayer instance;
	    return instance;
	}


	void play(const std::string sound)
	{
	    if (sounds_.count(sound))
	    {
	        sound_.setBuffer(sounds_[sound]);
	        sound_.play();
	    }

	}

private:
	SoundPlayer()
	{
	    sounds_["keytype"] 		= ResourceHolder::get().sounds.get("keytype");
	    sounds_["mistake"] 		= ResourceHolder::get().sounds.get("mistake");
	    sounds_["newline"] 		= ResourceHolder::get().sounds.get("newline");
	    sounds_["bell"] 		= ResourceHolder::get().sounds.get("bell");
	    sounds_["metro_bar"] 	= ResourceHolder::get().sounds.get("metro_bar");
	    sounds_["metro_beat"] 	= ResourceHolder::get().sounds.get("metro_beat");
	}

	std::map<std::string, sf::SoundBuffer> sounds_;
	sf::Sound sound_;
};

}
