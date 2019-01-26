#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <SFML/System.hpp>
#include "frameworkLib/Utilities.hpp"
#include "Misc.hpp"


namespace km
{

namespace fw = framework;

// Class responsible for loading words from file in UTF-8 format
class Dictionary
{
public:
    Dictionary(FilePath filePath);
    ~Dictionary() = default;
    Dictionary(const Dictionary&) = delete;
    const Dictionary& operator=(const Dictionary) = delete;
    Dictionary(Dictionary&&) = delete;
    Dictionary&& operator=(Dictionary&&) = delete;

    void loadFromFile(FilePath filePath);
    std::wstring getRandomWord();
    std::wstring getRandomWord(int length);	// should throw exception if length is to large, or specify available range in interface

    const std::wstring getText() const { return textFromFile_; }
    const std::vector<std::wstring> getLines() const { return lines_; }
    const std::set<std::wstring> getSetOfWords() const { return words_; }
    uint getLettersCount() const { return lettersCount_; }
    uint getWordsCount() const { return wordsCount_; }
    uint getLongestWord() const { return longestWord_; }
    uint getShortestWord() const { return shortestWord_; }

    std::wstring debugAllWordsString();

private:
    void prepareLines();
    void prepareWords();
    void sortWordsByLength();
    void prepareCounts();

    unsigned int lettersCount_;
    unsigned int wordsCount_;
    unsigned int longestWord_;
    unsigned int shortestWord_;

    std::wstring textFromFile_; // whole text as an one string
    std::vector <std::wstring> lines_; // arrays of lines from file
    std::set <std::wstring> words_; // each readed from file
    std::vector<std::wstring> wordsAll_; // store all words
    std::map<int, std::vector<std::wstring>> wordsByLength_; // store words by length
};

}
