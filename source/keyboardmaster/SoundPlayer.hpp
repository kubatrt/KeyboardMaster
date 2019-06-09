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
		if (!sounds_.count(sound))
		{
			sounds_[sound] = fw::ResourceHolder::get().sounds.get(sound);
		}
		sound_.setBuffer(sounds_[sound]);
		sound_.play();

	}

	SoundPlayer()
	{
	}

private:
	std::map<std::string, sf::SoundBuffer> sounds_;
	sf::Sound sound_;
};

}
