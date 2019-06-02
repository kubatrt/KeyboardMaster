#include "Dictionary.hpp"
#include "frameworkLib/Utilities.hpp"

namespace km
{

namespace
{
constexpr unsigned DEFAULT_SHORTEST_WORD = 3;
constexpr unsigned DEFAULT_LONGEST_WORD = 8;
}

Dictionary::Dictionary(FilePath filePath)
    : shortestWord_(DEFAULT_SHORTEST_WORD)
    , longestWord_(DEFAULT_LONGEST_WORD)
    , lettersCount_(0)
    , wordsCount_(0)
{
    loadFromFile(filePath);

    LOG_INFO(
    		"DICTIONARY CTOR: " << filePath.c_str() << std::endl
			<< "letters count: " << lettersCount_ << std::endl
			<< "longest word: " << longestWord_ << std::endl
			<< "shortest word: " << shortestWord_)
}

void Dictionary::loadFromFile(FilePath filePath)
{
    textFromFile_ = fw::loadTextFromUtf8File(filePath);
    textFromFile_ = textFromFile_.substr(1, textFromFile_.size() - 1); // my fix for the first letter

    prepareWords();
    prepareLines();
    prepareCounts();
    sortWordsByLength();
}

void Dictionary::prepareCounts()
{
    for (const auto& line : lines_)
    {
        lettersCount_ += line.length();
    }
}

void Dictionary::sortWordsByLength()
{
    for (auto& word : words_)
    {
        if (word.length() != 0)
        {
            wordsByLength_[word.length()].push_back(word);
        }
    }
}

std::wstring Dictionary::debugAllWordsString()
{
    std::wstringstream  wss;
    for (const auto& word : words_)
    {
        wss << word << " ";
    }
    return wss.str();
}

std::wstring Dictionary::getRandomWord()
{
    return wordsAll_.at( fw::RandomMachine::getRange<size_t>(0, wordsAll_.size() - 1) );
}

std::wstring Dictionary::getRandomWord(int length)
{
    if(length == getLongestWord())
        length--;
    return wordsByLength_[length].at(
            fw::RandomMachine::getRange<size_t>(0, wordsByLength_[length].size() - 1));
    
}

void Dictionary::prepareLines()
{
    std::wstring buffer;
    for (std::wstring::iterator it = textFromFile_.begin(); it != textFromFile_.end(); ++it)
    {
        if (*it == '\n')
        {
            lines_.push_back(buffer);
            buffer.clear();
        }
        else
        {
            buffer.push_back(*it);
        }
    }
    lines_.push_back(buffer);
}

void Dictionary::prepareWords()
{
    std::wstring buffer;
    for (std::wstring::iterator it = textFromFile_.begin(); it != textFromFile_.end(); ++it)
    {
        if (*it == ' ' || *it == '\n')
        {
            if (buffer.length() > longestWord_)
                longestWord_ = buffer.length();
            if (buffer.length() != 0 && buffer.length() < shortestWord_)
                shortestWord_ = buffer.length();

            wordsCount_++;
            words_.insert(buffer);

            buffer.clear();
        }
        else
        {
            buffer.push_back(*it);
        }
    }

    bool lastWord = !buffer.empty();
    if (lastWord)
    {
        wordsCount_++;
        words_.insert(buffer);
    }

    for(auto word : words_)
    {
        wordsAll_.push_back(word);
    }
}

}
