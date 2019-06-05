#include "GalleryGame.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

GalleryGame::GalleryGame(fw::GameBase& game, sf::Vector2u partition)
    : StateBase(game)
    , picture_(	game.getWindow().getSize().x,
    			game.getWindow().getSize().y,
				partition.x, partition.y,
				"obraz_1")
	, gameOver_(false)
{
    gameOverTextUI_.setCharacterSize(48);
    gameOverTextUI_.setFillColor(sf::Color::Magenta);
    gameOverTextUI_.setPosition({ game.getWindow().getSize().x / 2.f - 150.f, game.getWindow().getSize().y / 2.f - 50.f });
    gameOverTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    borderRectangle_.setPosition(4.f, 4.f);
    borderRectangle_.setSize(picture_.getSize());
    borderRectangle_.setOutlineThickness(4.f);
    borderRectangle_.setOutlineColor(sf::Color::Red);
    borderRectangle_.setFillColor(sf::Color::Black);

}

void GalleryGame::handleEvents(sf::Event e)
{
    // handle events

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
        {
        	// TODO: "are you sure?" window
            game_.popState();
        }
        else if (e.key.code == sf::Keyboard::Return)
        {
        	if(gameOver_)
        		game_.popState();
        }
        break;

    case sf::Event::TextEntered:
        textEnteredEvent(static_cast<wchar_t>(e.text.unicode));
        break;
    default:
        break;
    }
}

void GalleryGame::textEnteredEvent(wchar_t typedLetter)
{
    if (static_cast<int>(typedLetter) == KeyCode::Enter)
    {
        enterWord();
    }
    else
    {
        typedWord_ += typedLetter;
    }
}

void GalleryGame::enterWord()

{
    typedWords_++;
    picture_.wordTyped(typedWord_);
    typedWord_.clear();
    LOG_DEBUG("typedWords_ " << typedWords_);
}

void GalleryGame::update(sf::Time deltaTime)
{
    picture_.update(deltaTime);

    // GameOver
    if (picture_.isComplete())
    {
        gameOver_ = true;
        picture_.setVisible(true);
        std::stringstream ss; 
        ss << "WIN Picture: " << std::to_string(typedWords_) << " / "
            << std::to_string(picture_.elementsCount());
        gameOverTextUI_.setString(ss.str());
    }
    else if(typedWords_ >= picture_.elementsCount())
    {
    	gameOver_ = true;
    	picture_.setVisible(true);
    	std::stringstream ss;
		ss << "LOSE Picture: " << std::to_string(typedWords_) << " / "
			<< std::to_string(picture_.elementsCount());
		gameOverTextUI_.setString(ss.str());
    }
}

void GalleryGame::draw(sf::RenderTarget& renderer)
{
	renderer.draw(borderRectangle_);
    picture_.draw(renderer);

    if(gameOver_)
        renderer.draw(gameOverTextUI_);
}

}
