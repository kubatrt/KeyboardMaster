#pragma once

#include <climits>
#include <SFML/Graphics.hpp>
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"
#include "frameworkLib/Util/Animation.hpp"
#include "frameworkLib/Util/Logger.hpp"
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
		, velocity_({0,0})
		, moving_(false)
	{
		auto& explosion = explosionAnim_.createAnimation("Explode", "explosion", sf::seconds(1.5f), false);
		explosion.addFrames(sf::Vector2i(0,0), explosionSize_, 4);
		explosion.addFrames(sf::Vector2i(0,128), explosionSize_, 4);
		explosion.addFrames(sf::Vector2i(0,256), explosionSize_, 4);
		explosion.addFrames(sf::Vector2i(0,384), explosionSize_, 4);

		shipSprite_.setTexture(fw::ResourceHolder::get().textures.get("playerShip1_orange"));
		shipSprite_.setPosition(startingPosition_);
		targetX_ = startingPosition_.x;
	}

	void setTargetX(float x)
	{
		targetX_ = x;

		if(targetX_ > shipSprite_.getPosition().x)
		{
			velocity_ = sf::Vector2f(speed_, 0);
			moving_ = true;
		}
		else if(targetX_ < shipSprite_.getPosition().x)
		{
			velocity_ = sf::Vector2f(-speed_, 0);
			moving_ = true;
		}
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
			//if(shipSprite_.getPosition().x )
			// Stop ship
			unsigned distance = std::abs( shipSprite_.getPosition().x - targetX_);
			if(distance < 10)
			{
				moving_ = false;
			}

			LOG_CRITICAL("abs: " << distance);
			LOG_CRITICAL("position.x: " << shipSprite_.getPosition().x);
			LOG_CRITICAL("targetX: " << targetX_);

			if(moving_)
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
	bool moving_;
	bool isAlive_;
	sf::Vector2f velocity_;
	float targetX_;
	const float speed_ = 10.f;
	const sf::Vector2f startingPosition_ = {720,650};
	const sf::Vector2i explosionSize_ = {128,128};
	sf::Sprite	shipSprite_;
	sf::Sprite	explosionSprite_;
	fw::Animator explosionAnim_;
	// TODO: add positions
};

}

