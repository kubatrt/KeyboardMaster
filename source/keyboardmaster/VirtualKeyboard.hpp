#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "frameworkLib/IGameComponent.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"
#include "Misc.hpp"

namespace km
{

namespace fw = framework;
typedef unsigned int KeyCodeType;

namespace
{
constexpr float ROW_1ST = 4.f;
constexpr float ROW_2ND = 55.f;
constexpr float ROW_3RD = 107.f;
constexpr float ROW_4TH = 159.f;
constexpr float ROW_5TH = 210.f;
constexpr float OUT_OF_RANGE = 2000.0f;

KeyCodeType convertBigToSmallCharacter(KeyCodeType keycode)
{
	if(keycode >= 65 && keycode <= 90)
		return keycode + 32;

	return keycode;
}

KeyCodeType convertPolishCharacter(KeyCodeType keycode)
{
	switch(keycode)
	{
	case 380:
	case 379:
	case 378:
	case 377:
		keycode = KeyCode::z;
		break;
	case 260:
	case 261:
		keycode = KeyCode::a;
		break;
	case 262:
	case 263:
		keycode = KeyCode::c;
		break;
	case 280:
	case 281:
		keycode = KeyCode::e;
		break;
	case 321:
	case 322:
		keycode = KeyCode::l;
		break;
	case 211:
	case 243:
		keycode = KeyCode::o;
		break;
	case 323:
	case 324:
		keycode = KeyCode::n;
		break;
	default:
		break;
	}
	return keycode;
}

}

// Represents VirtualKeyboard game object
class VirtualKeyboard : fw::IGameComponent
{


public:
    VirtualKeyboard() = delete;
    ~VirtualKeyboard() = default;
    VirtualKeyboard(const VirtualKeyboard&) = delete;
    VirtualKeyboard& operator= (const VirtualKeyboard&) = delete;

    //void highlightLetter(int letterCode);

    VirtualKeyboard(sf::Vector2u windowSize)
    {
        maskPositions_[KeyCode::q] = sf::Vector2f(82, ROW_2ND);
        maskPositions_[KeyCode::w] = sf::Vector2f(134, ROW_2ND);
        maskPositions_[KeyCode::e] = sf::Vector2f(186, ROW_2ND);
        maskPositions_[KeyCode::r] = sf::Vector2f(238, ROW_2ND);
        maskPositions_[KeyCode::t] = sf::Vector2f(291, ROW_2ND);
        maskPositions_[KeyCode::y] = sf::Vector2f(343, ROW_2ND);
        maskPositions_[KeyCode::u] = sf::Vector2f(395, ROW_2ND);
        maskPositions_[KeyCode::i] = sf::Vector2f(447, ROW_2ND);
        maskPositions_[KeyCode::o] = sf::Vector2f(499, ROW_2ND);
        maskPositions_[KeyCode::p] = sf::Vector2f(551, ROW_2ND);
        maskPositions_[KeyCode::a] = sf::Vector2f(109, ROW_3RD);
        maskPositions_[KeyCode::s] = sf::Vector2f(161, ROW_3RD);
        maskPositions_[KeyCode::d] = sf::Vector2f(213, ROW_3RD);
        maskPositions_[KeyCode::f] = sf::Vector2f(266, ROW_3RD);
        maskPositions_[KeyCode::g] = sf::Vector2f(318, ROW_3RD);
        maskPositions_[KeyCode::h] = sf::Vector2f(370, ROW_3RD);
        maskPositions_[KeyCode::j] = sf::Vector2f(422, ROW_3RD);
        maskPositions_[KeyCode::k] = sf::Vector2f(474, ROW_3RD);
        maskPositions_[KeyCode::l] = sf::Vector2f(526, ROW_3RD);
        maskPositions_[KeyCode::semicolon] = sf::Vector2f(578, ROW_3RD);
        maskPositions_[KeyCode::apostrophe] = sf::Vector2f(631, ROW_3RD);
        maskPositions_[KeyCode::z] = sf::Vector2f(134, ROW_4TH);
        maskPositions_[KeyCode::x] = sf::Vector2f(186, ROW_4TH);
        maskPositions_[KeyCode::c] = sf::Vector2f(238, ROW_4TH);
        maskPositions_[KeyCode::v] = sf::Vector2f(290, ROW_4TH);
        maskPositions_[KeyCode::b] = sf::Vector2f(343, ROW_4TH);
        maskPositions_[KeyCode::n] = sf::Vector2f(395, ROW_4TH);
        maskPositions_[KeyCode::m] = sf::Vector2f(447, ROW_4TH);
        maskPositions_[KeyCode::EOL] = sf::Vector2f(683, ROW_3RD);      // when EOL press "Enter"
        maskPositions_[KeyCode::Enter] = sf::Vector2f(683, ROW_3RD);      // when EOL press "Enter"
        maskPositions_[KeyCode::Space] = sf::Vector2f(238, ROW_5TH);

        layoutTexture_ = fw::ResourceHolder::get().textures.get("kbl_48");
        layoutSprite_.setTexture(layoutTexture_);
        layoutSprite_.setPosition(0.f, static_cast<float>(windowSize.y - layoutTexture_.getSize().y));	// place at the bottom

        maskTexture_ = fw::ResourceHolder::get().textures.get("mask");
        maskSprite_.setTexture(maskTexture_);
        maskSprite_.setColor(sf::Color(255, 255, 255, 100));
    }

    void scalingKeyMask(KeyCodeType keycode)
    {
    	if(keycode == KeyCode::EOL || keycode == KeyCode::Enter)
    	{
    		maskSprite_.setScale(1.81f, 1.f);
    	}
    	else if(keycode == KeyCode::Space)
		{
			maskSprite_.setScale(5.36f, 1.f);
		}
    	else
    	{
    		maskSprite_.setScale(1.f, 1.f);
    	}
    }

    void highlightLetter(KeyCodeType characterCode)
    {
    	characterCode = convertPolishCharacter(characterCode);
    	characterCode = convertBigToSmallCharacter(characterCode);
        auto search = maskPositions_.find(characterCode);
        if (search != maskPositions_.end())
        {
            sf::Vector2f pos = search->second;
            scalingKeyMask(search->first);
            maskSprite_.setPosition(pos.x, pos.y + layoutSprite_.getPosition().y);
        }
        else
        {
            maskSprite_.setPosition(OUT_OF_RANGE, OUT_OF_RANGE);
        }
    }

    void update(sf::Time deltaTime)
    {

    }

    void draw(sf::RenderTarget& renderer)
    {
        renderer.draw(layoutSprite_);
        renderer.draw(maskSprite_);
    }

private:
    // Map <keyCode, Position> positions in relation to layout sprite
    std::map<KeyCodeType, sf::Vector2f> maskPositions_;
    sf::Texture layoutTexture_;
    sf::Sprite  layoutSprite_;
    sf::Texture maskTexture_;
    sf::Sprite  maskSprite_;
};

}   // km
