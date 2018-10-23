#include "WordsAttackGame.hpp"
#include <memory>
#include "../FrameworkLib/Util/Observer.hpp"
#include "../FrameworkLib/Util/Random.hpp"

namespace km
{

WordsAttackGame::WordsAttackGame(fw::GameBase& game)
    : StateBase(game)
    , dictionary_("D:/Workspace/Projects/Framework/Debug/data/words_01")
    , spawnInterval_(sf::seconds(1.f))
{
    typingTextUI_.setCharacterSize(24);
    typingTextUI_.setFillColor(sf::Color::Yellow);
    typingTextUI_.setPosition({50.f,(float)game.getWindow().getSize().y - 50 });
    typingTextUI_.setString("typingText");
    typingTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    scoreTextUI_.setCharacterSize(24);
    scoreTextUI_.setFillColor(sf::Color::Cyan);
    scoreTextUI_.setPosition({game.getWindow().getSize().x - 200.f, 50.f});
    scoreTextUI_.setString("Score:");
    scoreTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    livesTextUI_.setCharacterSize(24);
    livesTextUI_.setFillColor(sf::Color::Red);
    livesTextUI_.setPosition({ game.getWindow().getSize().x - 200.f, 100.f });
    livesTextUI_.setString("Lives:");
    livesTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    gameOverTextUI_.setCharacterSize(48);
    gameOverTextUI_.setFillColor(sf::Color::Magenta);
    gameOverTextUI_.setPosition({ game.getWindow().getSize().x /2.f - 150.f, game.getWindow().getSize().y / 2.f - 50.f});
    gameOverTextUI_.setString("Game Over");
    gameOverTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    horizontalLineUI_.setSize(sf::Vector2f(1024, 2));
    horizontalLineUI_.setPosition({0, (float)game.getWindow().getSize().y - 20});

    spawnWordBlock();
}

void WordsAttackGame::spawnWordBlock()
{
    if((wordBlocks_.size() >= maxWordsInGame) || gameOver)
        return;

    spawnClock_.restart();

    int wordLength = fw::RandomMachine::getRange(dictionary_.getShortestWord(), dictionary_.getLongestWord());
    std::wstring word = dictionary_.getRandomWord(wordLength);

    sf::Vector2f velocity(0, 1.f);
    static int spawnPoints[] = { 200, 400, 600, 800 };

    int spawnHorizontalPos = game_.getWindow().getSize().x / 2;
    int spawnHorizontalRanomPos = spawnPoints[fw::RandomMachine::getRange(0,3)];

    wordBlocks_.push_back( std::make_shared<WordBlock>(spawnHorizontalRanomPos, word, velocity));
}

void WordsAttackGame::handleEvents(sf::Event e)
{
    switch (e.type)
    {
    case sf::Event::KeyPressed:
        if (e.key.code == sf::Keyboard::Escape)
            game_.popState();
        else if (e.key.code == sf::Keyboard::F12)
            game_.toggleFullscreen();
        break;

        case sf::Event::TextEntered:
        typedLetter_ = static_cast<wchar_t>(e.text.unicode);

        if (static_cast<int>(typedLetter_) == KeyCode::Enter)
        {
            if(gameOver)
            {
                game_.popState();
            }
            else
            {
                // send to wordblock
                enterWord(typedWord_);
                typedWord_.clear();
            }
        }
        else if (static_cast<int>(typedLetter_) == KeyCode::Backspace)
        {
            if(typedWord_.size() > 0)
                typedWord_.pop_back();
        }
        else
        {
            if(gameOver)
                return;

            textEnteredEvent(typedLetter_);
        }
        break;
    default:
        break;
    }
}

void WordsAttackGame::textEnteredEvent(wchar_t letter)
{
    typedWord_ += letter;
}

void WordsAttackGame::enterWord(std::wstring word)
{
    for (auto &wb : wordBlocks_)
    {
        if (wb->getWord() == word)
        {
            wb->setAlive(false);
            score_ += 10 * wb->getWordLength();
            break;
        }
    }
}

void WordsAttackGame::destroyWord()
{

}


void WordsAttackGame::update(sf::Time deltaTime)
{
    if(lives == 0)
        gameOver = true;

    if (spawnClock_.getElapsedTime() >= spawnInterval_)
    {
        spawnClock_.restart();
        spawnWordBlock();
    }

    wordBlocks_.erase(std::remove_if(std::begin(wordBlocks_), std::end(wordBlocks_),
        [] (const auto& block) { return !block->isAlive(); }), std::end(wordBlocks_));

    for (auto &wb : wordBlocks_)
    {
        if(wb->getShape().getGlobalBounds().intersects(horizontalLineUI_.getGlobalBounds()))
        {
            wb->setAlive(false);
            lives--;
        }

        wb->update(deltaTime);
    }

    typingTextUI_.setString(typedWord_);
    scoreTextUI_.setString("Score: " + std::to_string(score_));
    livesTextUI_.setString("Lives: " + std::to_string(lives));
}

void WordsAttackGame::draw(sf::RenderTarget& renderer)
{
    for (auto &wb : wordBlocks_)
    {
        wb->draw(renderer);
    }
    if(gameOver)
        renderer.draw(gameOverTextUI_);
    
    renderer.draw(typingTextUI_);
    renderer.draw(scoreTextUI_);
    renderer.draw(livesTextUI_);
    renderer.draw(horizontalLineUI_);
}

}
