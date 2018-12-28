#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Misc.hpp"
#include "Dictionary.hpp"
#include "frameworkLib/Utilities.hpp"

namespace km
{

// TODO: What exatly this class should do? Gather input form player
// - counting mistakes
// - collecting typed words
// - calculating game stats
class KeyboardTyper
{
public:
    KeyboardTyper();
    ~KeyboardTyper() = default;
    KeyboardTyper(const KeyboardTyper&) = delete;
    KeyboardTyper(KeyboardTyper&&) = delete;
    KeyboardTyper& operator=(const KeyboardTyper&) = delete;
    KeyboardTyper& operator=(KeyboardTyper&&) = delete;

    float getKPM() const { return keysPerMinute_; }
    float getWPM() const { return wordsPerMinute_; }
    

    float correctnessPercentage(uint lettersCount);

    void textEnteredEvent(wchar_t letter, bool correct, uint letterPositionInLine);
    void wordEntered(std::wstring word, bool correct = true);

    //void backspace();
    //void mistake();
    void omit(uint lettersNumber);
    uint getOmittedLetters() const { return omittedLetters_; }
    uint getBackspaces() const; 
    uint getMistakes() const;
    uint getCorrectLetters() const { return correctLetters_; }
    uint getCorrectWords() const { return correctWords_;}
    uint getTypedKeys() const { return typedKeys_; }

    void update(sf::Time deltaTime);

private:
    // Dictionary dictionary_;
    sf::Clock timer_;
    std::wstring typingText_;
    std::vector<std::wstring> typedWords_;

    wchar_t lastTypedLetter_;
    std::wstring lastTypedWord_;
    uint correctWords_;

    //float correctness_;
    //uint wordsTotal_;
    uint backspaces_;
    uint correctLetters_;
    uint omittedLetters_;
    uint mistakeLetters_;

    uint typedKeys_;    	// every key typed
    uint wordsTyped_;		// typed words counter
    float keysPerMinute_;
    float wordsPerMinute_;
};

} // km
