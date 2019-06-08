#include <memory>
#include <array>
#include "WordsAttackGame.hpp"
#include "SoundPlayer.hpp"
#include "frameworkLib/Util/Observer.hpp"
#include "frameworkLib/Util/Random.hpp"

namespace km
{

namespace
{
//std::array<float, 9> SpawnHorizontalPositions = { 0.f, 100.f, 200.f, 300.f, 400.f, 500.f, 600.f, 700.f, 800.f };
constexpr float MaxSpawnHorizontalPosition = 800.f;
std::array<float, 3> VelocityTable = { 1.5f, 1.75f, 2.f };

constexpr float MaxVerticalVelocity = 2.f;
constexpr float MinVerticalVelocity = 1.f;
constexpr int ScoreMultiplier = 10;

constexpr float MinSpawnInterval = 0.5f;
constexpr float SpawnInterval = 0.8f;
constexpr float IntervalDecrementStep = 0.05f;
constexpr float IntervalDecrementTreshold = 5.0f; //	change every 5 seconds
//constexpr float MinSpawnInterval = 0.5f;
}

WordsAttackGame::WordsAttackGame(fw::GameBase& game, const AssetName dictionaryFile)
    : StateBase(game)
    , dictionary_(dictionaryFile)
    , spawnInterval_(sf::seconds(SpawnInterval))
	, spawnScheduler_(sf::seconds(SpawnInterval))
	, spawnDecrementScheduler_(sf::seconds(IntervalDecrementTreshold))
{
	backgroundSpriteUI_.setTexture(fw::ResourceHolder::get().textures.get("deep-blue-space"));

    typingTextUI_.setCharacterSize(24);
    typingTextUI_.setFillColor(sf::Color::Yellow);
    typingTextUI_.setPosition({50.f,(float)game.getWindow().getSize().y - 50 });
    typingTextUI_.setString("");
    typingTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));


    timerTextUI_.setCharacterSize(24);
    timerTextUI_.setFillColor(sf::Color::Cyan);
    timerTextUI_.setPosition({game.getWindow().getSize().x - 200.f, 10.f});
    timerTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));


    scoreTextUI_.setCharacterSize(24);
    scoreTextUI_.setFillColor(sf::Color::Yellow);
    scoreTextUI_.setPosition({game.getWindow().getSize().x - 200.f, 50.f});
    scoreTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    livesTextUI_.setCharacterSize(24);
    livesTextUI_.setFillColor(sf::Color::Red);
    livesTextUI_.setPosition({ game.getWindow().getSize().x - 200.f, 90.f });
    livesTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    gameOverTextUI_.setCharacterSize(48);
    gameOverTextUI_.setFillColor(sf::Color::Magenta);
    gameOverTextUI_.setPosition({ game.getWindow().getSize().x /2.f - 150.f, game.getWindow().getSize().y / 2.f - 50.f});
    gameOverTextUI_.setString("Koniec!");
    gameOverTextUI_.setFont(fw::ResourceHolder::get().fonts.get("arial"));

    horizontalLineUI_.setSize(sf::Vector2f(1024, 2));
    horizontalLineUI_.setPosition({0, (float)game.getWindow().getSize().y - 20});

    spawnScheduler_.setCallback(
    	[&]() {
    	spawnWordBlock();
    	spawnScheduler_.restart();
    });
    spawnScheduler_.start();

    spawnDecrementScheduler_.setCallback(
    	[&]() {
    	spawnInterval_ -= sf::seconds(IntervalDecrementStep);
    	spawnScheduler_.setTreshold(spawnInterval_);
    	spawnDecrementScheduler_.restart();
    	LOG_DEBUG(">>> Increse speed: " << spawnInterval_.asSeconds());
    });
    spawnDecrementScheduler_.start();

    spawnWordBlock();	// spawn first
}

void WordsAttackGame::spawnWordBlock()
{
    if((wordBlocks_.size() >= maxWordsInGame) || gameOver)
        return;

    int wordLength = fw::RandomMachine::getRange(dictionary_.getShortestWord(), dictionary_.getLongestWord());
    std::wstring word = dictionary_.getRandomWord(wordLength);

    float verticalVelocity = 1.f;
    // Use function scaleBetween(unscaledNum, minAllowed, maxAllowed, min, max)
    //auto longest = dictionary_.getLongestWord();
    //auto shortest = dictionary_.getShortestWord();
    // TODO: so ugly, use range transformation for this!
    if(word.length() < 4)
    	verticalVelocity = VelocityTable[2];
    else if(word.length() >= 4 && word.length() <= 5)
    	verticalVelocity = VelocityTable[1];
    else
    	verticalVelocity = VelocityTable[0];

    // Randomize it by 10 step,
    float randomHorizontalPosition = static_cast<float>(fw::RandomMachine::getRange(1, 10) / 10.f) * MaxSpawnHorizontalPosition;

    wordBlocks_.push_back(std::make_unique<WordBlock>(randomHorizontalPosition, word, verticalVelocity));
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

        if (static_cast<int>(typedLetter_) == KeyCode::Enter) // PUSH ENTER
        {
            if(gameOver)
            {
                game_.popState();
            }
            else
            {
                // send 'word' to wordblock
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

void WordsAttackGame::addScore(int wordLength)
{
	score_ += ScoreMultiplier * wordLength;
	SoundPlayer::getInstance()->play("pop");
}

void WordsAttackGame::enterWord(std::wstring word)
{
    for (auto &wb : wordBlocks_)
    {
        if (wb->getWord() == word)
        {
            wb->setAlive(false);
            addScore(wb->getWordLength());
            break;
        }
    }
}


void WordsAttackGame::update(sf::Time deltaTime)
{
	if(gameOver)
		return;

    if(lives == 0)
        gameOver = true;

	gameTime_ += deltaTime;
	spawnScheduler_.update();
	spawnDecrementScheduler_.update();

    // Remove marked blocks
    wordBlocks_.erase(std::remove_if(std::begin(wordBlocks_), std::end(wordBlocks_),
        [] (const auto& block) { return !block->isAlive(); }), std::end(wordBlocks_));

    for (auto &wordBlock : wordBlocks_)
    {
        if(wordBlock->getShape().getGlobalBounds().intersects(horizontalLineUI_.getGlobalBounds()))
        {
            wordBlock->setAlive(false);
            lives--;
        }
        wordBlock->update(deltaTime);
    }

    typingTextUI_.setString(typedWord_);
    timerTextUI_.setString(L"Czas: " + std::to_wstring(static_cast<int>(gameTime_.asSeconds())) );
    scoreTextUI_.setString(L"Punkty: " + std::to_wstring(score_));
    livesTextUI_.setString(L"Życia: " + std::to_wstring(lives));
}

void WordsAttackGame::draw(sf::RenderTarget& renderer)
{
	renderer.draw(backgroundSpriteUI_);
    if(gameOver)
    {
        renderer.draw(gameOverTextUI_);
    }
    else
    {
        for (auto &wb : wordBlocks_)
        {
            wb->draw(renderer);
        }
        renderer.draw(typingTextUI_);
    }

    renderer.draw(timerTextUI_);
    renderer.draw(scoreTextUI_);
    renderer.draw(livesTextUI_);
    renderer.draw(horizontalLineUI_);
}

}
