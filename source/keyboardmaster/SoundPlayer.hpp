#pragma once

#include <map>
#include <string>
#include <SFML/Audio.hpp>
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"
#include "frameworkLib/Util/Singleton.hpp"

namespace km
{

namespace fw = framework;


class SoundPlayer : public fw::Singleton<SoundPlayer>
{
public:
	~SoundPlayer() = default;
	SoundPlayer(const fw::ResourceHolder&) = delete;
	SoundPlayer(fw::ResourceHolder&&) = delete;
	SoundPlayer& operator=(const SoundPlayer&) = delete;
	SoundPlayer& operator=(SoundPlayer&&) = delete;

	void play(const std::string sound)
	{
	    if (sounds_.count(sound))
	    {
	        sound_.setBuffer(sounds_[sound]);
	        sound_.play();
	    }

	}

	SoundPlayer()
	{
	    sounds_["keytype"] 		= fw::ResourceHolder::get().sounds.get("keytype");
	    sounds_["mistake"] 		= fw::ResourceHolder::get().sounds.get("mistake");
	    sounds_["newline"] 		= fw::ResourceHolder::get().sounds.get("newline");
	    sounds_["bell"] 		= fw::ResourceHolder::get().sounds.get("bell");
	    sounds_["metro_bar"] 	= fw::ResourceHolder::get().sounds.get("metro_bar");
	    sounds_["metro_beat"] 	= fw::ResourceHolder::get().sounds.get("metro_beat");
	    sounds_["bang"] 		= fw::ResourceHolder::get().sounds.get("bang");
	    sounds_["pop"] 			= fw::ResourceHolder::get().sounds.get("pop");
	    sounds_["tap"] 			= fw::ResourceHolder::get().sounds.get("tap");
	    sounds_["reveal"] 		= fw::ResourceHolder::get().sounds.get("reveal");
	}

private:
	std::map<std::string, sf::SoundBuffer> sounds_;
	sf::Sound sound_;
};

}
