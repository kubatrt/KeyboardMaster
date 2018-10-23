#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "../FrameworkLib/IGameComponent.hpp"
#include "../FrameworkLib/ResourceManager/ResourceHolder.hpp"
#include "Misc.hpp"

namespace km
{

constexpr float row_1st = 4;
constexpr float row_2nd = 55;
constexpr float row_3rd = 107;
constexpr float row_4th = 159;
constexpr float row_5th = 210;
constexpr float OUT_OF_RANGE = 2000.0f;

class VirtualKeyboard : IGameComponent
{
public:
    //VirtualKeyboard();
    //VirtualKeyboard(sf::Vector2u windowSize);
    ~VirtualKeyboard() = default;

    VirtualKeyboard(const VirtualKeyboard&) = delete;
    VirtualKeyboard& operator= (const VirtualKeyboard&) = delete;

    //void highlightLetter(int letterCode);

    sf::Texture layoutTexture_;
    sf::Texture maskTexture_;
    sf::Sprite  layoutSprite_;
    sf::Sprite  maskSprite_;


    VirtualKeyboard(sf::Vector2u windowSize)
    {
        maskPositions_[KeyCode::q] = sf::Vector2f(82, row_2nd);
        maskPositions_[KeyCode::w] = sf::Vector2f(134, row_2nd);
        maskPositions_[KeyCode::e] = sf::Vector2f(186, row_2nd);
        maskPositions_[KeyCode::r] = sf::Vector2f(238, row_2nd);
        maskPositions_[KeyCode::t] = sf::Vector2f(291, row_2nd);
        maskPositions_[KeyCode::y] = sf::Vector2f(343, row_2nd);
        maskPositions_[KeyCode::u] = sf::Vector2f(395, row_2nd);
        maskPositions_[KeyCode::i] = sf::Vector2f(447, row_2nd);
        maskPositions_[KeyCode::o] = sf::Vector2f(499, row_2nd);
        maskPositions_[KeyCode::p] = sf::Vector2f(551, row_2nd);
        maskPositions_[KeyCode::a] = sf::Vector2f(109, row_3rd);
        maskPositions_[KeyCode::s] = sf::Vector2f(161, row_3rd);
        maskPositions_[KeyCode::d] = sf::Vector2f(213, row_3rd);
        maskPositions_[KeyCode::f] = sf::Vector2f(266, row_3rd);
        maskPositions_[KeyCode::g] = sf::Vector2f(318, row_3rd);
        maskPositions_[KeyCode::h] = sf::Vector2f(370, row_3rd);
        maskPositions_[KeyCode::j] = sf::Vector2f(422, row_3rd);
        maskPositions_[KeyCode::k] = sf::Vector2f(474, row_3rd);
        maskPositions_[KeyCode::l] = sf::Vector2f(526, row_3rd);
        maskPositions_[KeyCode::semicolon] = sf::Vector2f(578, row_3rd);
        maskPositions_[KeyCode::apostrophe] = sf::Vector2f(631, row_3rd);
        maskPositions_[KeyCode::z] = sf::Vector2f(134, row_4th);
        maskPositions_[KeyCode::x] = sf::Vector2f(186, row_4th);
        maskPositions_[KeyCode::c] = sf::Vector2f(238, row_4th);
        maskPositions_[KeyCode::v] = sf::Vector2f(290, row_4th);
        maskPositions_[KeyCode::b] = sf::Vector2f(343, row_4th);
        maskPositions_[KeyCode::n] = sf::Vector2f(395, row_4th);
        maskPositions_[KeyCode::m] = sf::Vector2f(447, row_4th);
        maskPositions_[KeyCode::EOL] = sf::Vector2f(683, row_3rd);      // when EOL press "Enter"
        maskPositions_[KeyCode::Space] = sf::Vector2f(238, row_5th);


        layoutTexture_ = framework::ResourceHolder::get().textures.get("kbl_48");
        layoutSprite_.setTexture(layoutTexture_);
        layoutSprite_.setPosition(0.f, static_cast<float>(windowSize.y - layoutTexture_.getSize().y));

        maskTexture_ = framework::ResourceHolder::get().textures.get("mask");
        maskSprite_.setTexture(maskTexture_);
        maskSprite_.setColor(sf::Color(255, 255, 255, 100));
    }

    void highlightLetter(int letterCode)
    {
        auto search = maskPositions_.find(letterCode);
        if (search != maskPositions_.end())
        {
            sf::Vector2f pos = search->second;
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
    // <keyCode, Position> positions in relation to layout sprite
    std::map<int, sf::Vector2f> maskPositions_;
};

}   // km