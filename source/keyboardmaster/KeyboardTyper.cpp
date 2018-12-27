#include "KeyboardTyper.hpp"


namespace km
{

KeyboardTyper::KeyboardTyper()
	: wordsPerMinute_(0.f)
	, keysPerMinute_(0.f)
	, wordsTyped_(0)
	, lastTypedLetter_(L' ')
	, lastTypedWord_(L"")
	, correctWords_(0)
	, backspaces_(0)
	, correctLetters_(0)
	, omittedLetters_(0)
	, mistakeLetters_(0)
	, typedKeys_(0)
{
    timer_.restart();
} 


void KeyboardTyper::omit(uint lettersNumber)
{
    omittedLetters_ += lettersNumber;
}

uint KeyboardTyper::getMistakes() const
{
    return mistakeLetters_;
}

/*
void KeyboardTyper::mistake()
{
    mistakeLetters_++;
}

void KeyboardTyper::backspace()
{
    backspaces_++;
}
*/

uint KeyboardTyper::getBackspaces() const
{
    return backspaces_;
}

void KeyboardTyper::textEnteredEvent(wchar_t letter, bool correct, uint letterPositionInLine)
{
    if (static_cast<int>(letter) == KeyCode::Backspace)
    {
        if(letterPositionInLine > 0)
            backspaces_++;
    }
    else if(static_cast<int>(letter) == KeyCode::Enter)
    {
        typedKeys_++;
    }
    else
    {
        typedKeys_++;

        if (backspaces_ > 0)
        {
            backspaces_--;
        }
        else
        {
            if (correct) 
                correctLetters_++;
            else
                mistakeLetters_++;
        }
    }
    lastTypedLetter_ = letter;
    typingText_.append({letter});
}

void KeyboardTyper::wordEntered(std::wstring word, bool correct)
{
    typedWords_.push_back(word);
    lastTypedWord_ = word;
    if(correct) correctWords_++;
}

void KeyboardTyper::update(sf::Time deltaTime)
{
    sf::Time elapsed = timer_.getElapsedTime();
    keysPerMinute_ = (typedKeys_ > 0) ? typedKeys_ / elapsed.asSeconds() * 60.f : 0;
    wordsPerMinute_ = (wordsPerMinute_ > 0) ? wordsPerMinute_ / elapsed.asSeconds() * 60.f : 0;
}

float KeyboardTyper::correctnessPercentage(uint lettersCount)
{
    return (mistakeLetters_ == 0 && omittedLetters_ == 0) ? 100.f
    		: 100.f - (static_cast<float>((mistakeLetters_ + omittedLetters_)) / lettersCount * 100.f);
}

}
