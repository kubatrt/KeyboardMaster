#pragma once

#include "frameworkLib/GameBase.hpp"
#include "frameworkLib/StateBase.hpp"
#include "WordBlock.hpp"
#include "Dictionary.hpp"
#include "Scheduler.hpp"

namespace km
{

namespace fw = framework;

class WordsAttackGame : public fw::StateBase
{
public:
    WordsAttackGame(fw::GameBase& game, const AssetName dictionaryFile);

    void handleEvents(sf::Event e) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& renderer) override;

    void textEnteredEvent(wchar_t letter);
    void enterWord(std::wstring word);

private:
    void addScore(int wordLength);
    void spawnWordBlock();

    std::vector<std::unique_ptr<WordBlock>> wordBlocks_;
    Dictionary dictionary_;

    wchar_t typedLetter_;
    std::wstring typedWord_;

    int score_ = 0;
    int lives = 3;
    int maxWordsInGame = 10;

    int missedWords = 0;
    int wordsInGame = 0;
    bool gameOver = false;
    
    Scheduler spawnScheduler_;
    Scheduler spawnDecrementScheduler_;
    sf::Clock spawnClock_;
    sf::Time spawnInterval_;
    sf::Time gameTime_;

    // GUI
    sf::Sprite backgroundSpriteUI_;
    sf::RectangleShape horizontalLineUI_;
    sf::Text typingTextUI_;
    sf::Text scoreTextUI_;
    sf::Text livesTextUI_;
    sf::Text timerTextUI_;
    sf::Text gameOverTextUI_;
};

}
