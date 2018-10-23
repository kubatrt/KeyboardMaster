#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Misc.hpp"
#include "Dictionary.hpp"
#include "../FrameworkLib/Utilities.hpp"

namespace km
{

// TODO What exatly this class should do?
//  - counting mistakes
//  - collecting typed words
//  - calculating stats

class KeyboardTyper : public framework::NonCopyable
{
public:
    KeyboardTyper();
    ~KeyboardTyper();

    float getKPM() const { return keysPerMinute_; }
    float getKPW() const { return wordsPerMinute_; }
    
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

    std::wstring debugInfo() {};

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

    unsigned int typedKeys_;    // every key typed
    unsigned int wordsTyped_;
    float keysPerMinute_;
    float wordsPerMinute_;
};

} // km