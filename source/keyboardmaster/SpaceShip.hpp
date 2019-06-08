#pragma once

#include <SFML/Graphics.hpp>
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"
#include "frameworkLib/Util/Animation.hpp"
#include "SoundPlayer.hpp"

namespace km
{

namespace fw = framework;

class SpaceShip
{
public:
	SpaceShip()
		: explosionAnim_(explosionSprite_)
		, isAlive_(true)
		, targetX_(startingPosition_.x)
		, velocity_({0,0})
	{
		auto& explosion = explosionAnim_.createAnimation("Explode", "explosion", sf::seconds(1.5f), false);
		explosion.addFrames(sf::Vector2i(0,0), explosionSize_, 4);
		explosion.addFrames(sf::Vector2i(0,128), explosionSize_, 4);
		explosion.addFrames(sf::Vector2i(0,256), explosionSize_, 4);
		explosion.addFrames(sf::Vector2i(0,384), explosionSize_, 4);

		shipSprite_.setTexture(fw::ResourceHolder::get().textures.get("playerShip1_orange"));
		shipSprite_.setPosition(startingPosition_);

	}

	void setTargetX(float x)
	{
		targetX_ = x;
		if(targetX_ > shipSprite_.getPosition().x)
			velocity_ = sf::Vector2f(speed, 0);
		else
			velocity_ = sf::Vector2f(-speed, 0);
	}

	void kill()
	{
		isAlive_ = false;
		SoundPlayer::getInstance()->play("explosion");
	}

	void update(sf::Time deltaTime)
	{
		explosionSprite_.setPosition(shipSprite_.getPosition());
		if(isAlive_)
		{
			if(shipSprite_.getPosition().x != targetX_)
						shipSprite_.move(velocity_);
		}
		else
		{
			explosionAnim_.update(deltaTime);
		}
	}

	void draw(sf::RenderTarget& renderer)
	{

		if(isAlive_)
			renderer.draw(shipSprite_);
		else
			renderer.draw(explosionSprite_);
	}

private:
	bool isAlive_;
	sf::Vector2f velocity_;
	float targetX_;
	const float speed = 5.f;
	const sf::Vector2f startingPosition_ = {720,650};
	const sf::Vector2i explosionSize_ = {128,128};
	sf::Sprite	shipSprite_;
	sf::Sprite	explosionSprite_;
	fw::Animator explosionAnim_;
	// TODO: add positions
};

}

