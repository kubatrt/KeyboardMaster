#include "Dictionary.hpp"
#include "frameworkLib/Utilities.hpp"

namespace km
{

Dictionary::Dictionary(FilePath filePath)
    : shortestWord_(0)
    , longestWord_(0)
    , lettersCount_(0)
    , wordsCount_(0)
{
    loadFromFile(filePath);

    LOG_INFO("DICTIONARY CTOR: " << filePath.c_str() << std::endl
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
    return wordsAll_.at( fw::RandomMachine::getRange<size_t>(0, wordsAll_.size()-1) );
}

std::wstring Dictionary::getRandomWord(int length)
{
    if(length > getLongestWord())
        length = getLongestWord();
    if(length < getShortestWord())
    	length = getShortestWord();

    // workaround, if no word with specified length, chose lower bound
    if(wordsByLength_[length].size() == 0)
    	length = *availableWordsLength_.lower_bound(length);

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
        	auto bufferWordLength = buffer.length();
        	availableWordsLength_.emplace(bufferWordLength);

        	// initialize, assign the first word
        	if(shortestWord_ == 0)
        	{
        		shortestWord_ = bufferWordLength;
        	}
        	if(longestWord_ == 0)
        	{
        		longestWord_ = bufferWordLength;
        	}

            if (bufferWordLength > longestWord_)
            {
                longestWord_ = bufferWordLength;
            }
            if (bufferWordLength < shortestWord_)
            {
                shortestWord_ = bufferWordLength;
            }

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
