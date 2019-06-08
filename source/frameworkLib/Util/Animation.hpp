#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

namespace framework
{

class Animator
{
public:
	struct Animation
	{
		std::string name_;
		std::string textureName_;
		std::vector<sf::IntRect> frames_;
		sf::Time duration_;
		bool looping_;

		Animation(const std::string& name, const std::string& textureName,
			const sf::Time& duration, bool looping)
			: name_(name)
			, textureName_(textureName)
			, duration_(duration)
			, looping_(looping)
		{

		}

		void addFrames(sf::Vector2i startFrom, sf::Vector2i frameSize, unsigned int frames)
		{
			sf::Vector2i current = startFrom;
			for(unsigned int i=0; i < frames; ++i)
			{
				frames_.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
				current.x += frameSize.x;
			}
		}
	};

	Animator(sf::Sprite& sprite);
	Animator::Animation& createAnimation(const std::string& name,
			const std::string& textureName, sf::Time duration, bool loop = false);
	bool switchAnimation(const std::string& name);
	std::string getCurrentAnimationName() const;

	void update(sf::Time deltaTime);


private:
	// Return animation with given name, nullptr if not found
	Animator::Animation* findAnimation(const std::string& name);
	void switchAnimation(Animator::Animation* animation);

	sf::Sprite& sprite_;
	sf::Time currentTime_;
	std::list<Animator::Animation> animations_;
	Animator::Animation* currentAnimation_;
};

}   // framework
