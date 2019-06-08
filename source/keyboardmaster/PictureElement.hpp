#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "frameworkLib/Utilities.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"
#include "Misc.hpp"
#include "Scheduler.hpp"

namespace km
{

class Picture;

//
// Represent one piece of picture
//
class PictureElement
{
public:
	PictureElement(
			sf::Texture& texture,
			sf::IntRect textureSectionRect,
			sf::Vector2f position,
			uint index,
			std::wstring word);
	PictureElement(const PictureElement& pe) = delete;
	~PictureElement();

	size_t getWordLength() { return word_.length(); }
	std::wstring getWord() { return word_; }
	uint getIndex() const { return index_; }
	bool isRevealed() const { return revealed_; }
	bool isMissed() const { return missed_; }
	bool isActive() const { return active_; }
	void setActive() { active_ = true; 	scheduler_.start(); }

	void reveal();
	void miss();

	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget& renderer);

private:
    sf::Sprite sprite_;
    sf::Text wordText_;
    std::wstring word_;
    bool active_;	// is it current active element? Can by only one at time
    bool revealed_;	// is picture revealed as a whole?
    bool missed_;	// is it was missed?

    const uint index_;
    wchar_t nextLetter_;
    Scheduler scheduler_;
};

}
