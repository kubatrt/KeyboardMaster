#include "Animation.hpp"
#include "../ResourceManager/ResourceHolder.hpp"

namespace framework
{

Animator::Animator(sf::Sprite& sprite)
	: sprite_(sprite)
	, currentTime_()
	, currentAnimation_(nullptr)
{

}

Animator::Animation& Animator::createAnimation(const std::string& name, const std::string& textureName, sf::Time duration, bool loop)
{
	animations_.push_back( Animator::Animation(name, textureName, duration, loop));

	if(currentAnimation_ == nullptr)
		switchAnimation(&animations_.back());

	return animations_.back();
}

void Animator::switchAnimation(Animator::Animation* animation)
{
	if(animation != nullptr)
	{
		sprite_.setTexture(ResourceHolder::get().textures.get(animation->textureName_));
	}
	currentAnimation_ = animation;
	currentTime_ = sf::Time::Zero;
}

bool Animator::switchAnimation(const std::string& name)
{
	auto animation = findAnimation(name);
	if(animation != nullptr)
	{
		switchAnimation(animation);
		return true;
	}
	return false;
}

Animator::Animation* Animator::findAnimation(const std::string& name)
{
	for(auto it = animations_.begin(); it != animations_.end(); ++it)
	{
		if(it->name_ == name)
			return &(*it);
	}

	return nullptr;
}

std::string Animator::getCurrentAnimationName() const
{
	if(currentAnimation_ != nullptr)
		return currentAnimation_->name_;

	// if no animation is playing, return empty string
	return "";
}

void Animator::update(sf::Time deltaTime)
{
	if(currentAnimation_ == nullptr)
		return;

	currentTime_ += deltaTime;

	float scaledTime = (currentTime_.asSeconds() / currentAnimation_->duration_.asSeconds());
	int numFrames = currentAnimation_->frames_.size();
	int currentFrame = static_cast<int>(scaledTime * numFrames);

	if(currentAnimation_->looping_)
		currentFrame %= numFrames;
	else if(currentFrame >= numFrames)
		currentFrame = numFrames - 1;

	sprite_.setTextureRect(currentAnimation_->frames_[currentFrame]);
}


}   // framework
