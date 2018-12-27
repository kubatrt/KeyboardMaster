#include "GalleryGame.hpp"
#include "frameworkLib/ResourceManager/ResourceHolder.hpp"

namespace km
{

GalleryGame::GalleryGame(fw::GameBase& game, sf::Vector2u partition)
    : StateBase(game)
    , picture_(game.getWindow().getSize().x, game.getWindow().getSize().y, partition.x, partition.y)
	, gameOver_(false)
{
    gameOverTextUI_.setCharacterSize(48);
    gameOverTextUI_.setFillColor(sf::Color::Magenta);
    gameOverTextUI_.setPosition({ game.getWindow().getSize().x / 2.f - 150.f, game.getWindow().getSize().y / 2.f - 50.f });
    gameOverTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));
}

void GalleryGame::handleEvents(sf::Event e)
{
    // handle events

    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
        {
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
    std::wcout << "Entered word: " << typedWord_ << std::endl;
    typedWords_++;
    picture_.typedWord(typedWord_);
    typedWord_.clear();
}

void GalleryGame::update(sf::Time deltaTime)
{
    picture_.update(deltaTime);

    if (picture_.isComplete() || typedWords_ == picture_.elementsCount())
    {
        gameOver_ = true;
        picture_.setVisible(true);
        std::stringstream ss; 
        ss << "[debug] Picture: " << std::to_string(typedWords_) << " / " 
            << std::to_string(picture_.elementsCount());
        gameOverTextUI_.setString(ss.str());
    }
}

void GalleryGame::draw(sf::RenderTarget& renderer)
{
    picture_.draw(renderer);
    if(gameOver_)
        renderer.draw(gameOverTextUI_);
}

}
