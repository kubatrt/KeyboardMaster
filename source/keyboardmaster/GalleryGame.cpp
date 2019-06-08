#include "GalleryGame.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

namespace
{
sf::Color fontColor = sf::Color::Red;
sf::Color borderColor = sf::Color::Red;
}


GalleryGame::GalleryGame(fw::GameBase& game, uint rows, uint cols, AssetName picture)
    : StateBase(game)
    , picture_(rows, cols, picture)

{
    gameOverTextUI_.setCharacterSize(48);
    gameOverTextUI_.setFillColor(fontColor);
    gameOverTextUI_.setPosition({ game.getWindow().getSize().x / 2.f - 250.f, game.getWindow().getSize().y / 2.f - 50.f });
    gameOverTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    timerTextUI_.setCharacterSize(32);
    timerTextUI_.setFillColor(fontColor);
    timerTextUI_.setPosition({ game.getWindow().getSize().x - 80.f, 30.f });
    timerTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));


    borderRectangle_.setPosition(0.f, 0.f);
    borderRectangle_.setSize( sf::Vector2f( picture_.getSize().x , picture_.getSize().y) );
    borderRectangle_.setOutlineThickness(-4.f);
    borderRectangle_.setOutlineColor(borderColor);
    borderRectangle_.setFillColor(sf::Color::Transparent);

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
	if(gameOver_)
		return;

    picture_.update(deltaTime);
    timerTextUI_.setString(std::to_string(
    		static_cast<int>(timer_.getElapsedTime().asSeconds())));

    // GameOver
    if (picture_.isComplete())
    {
        gameOver_ = true;

        picture_.setVisible(true);
        std::stringstream ss; 
        ss << "WYGRANA! : " << std::to_string(picture_.reveleadElementsCount()) << " / "
            << std::to_string(picture_.elementsCount()) << " CZAS: " << static_cast<int>(timer_.getElapsedTime().asSeconds());
        gameOverTextUI_.setString(ss.str());

    }
    else if(typedWords_ >= picture_.elementsCount())
    {
    	gameOver_ = true;
    	//picture_.setVisible(true);
    	std::stringstream ss;
		ss << "PRZEGRANA! : " << std::to_string(picture_.reveleadElementsCount()) << " / "
			<< std::to_string(picture_.elementsCount()) << " CZAS: " << static_cast<int>(timer_.getElapsedTime().asSeconds());
		gameOverTextUI_.setString(ss.str());
    }
}

void GalleryGame::draw(sf::RenderTarget& renderer)
{
    picture_.draw(renderer);
    renderer.draw(borderRectangle_);

    if(gameOver_)
        renderer.draw(gameOverTextUI_);
    renderer.draw(timerTextUI_);
}

}
