#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <vector>
#include <string>
#include "Files.hpp"


namespace framework
{

std::string loadTextFromFile(const std::string& filePath, bool throws)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::string error = "Unable to open file: " + filePath + "!";
        if (throws)
        {
            throw std::runtime_error(error);
        }
        else
        {
            std::cerr << error << '\n';
        }
    }

    std::ostringstream oss;
    oss << inFile.rdbuf();
    return oss.str();
}

// System independent, universal utf8 text file loading
std::wstring loadTextFromUtf8File(const std::string& filePath, bool throws)
{
    std::wifstream wif(filePath.c_str());
    if (!wif.is_open())
    {
        std::string error = "Unable to open file: " + filePath;
        if (throws)
        {
            throw std::runtime_error(error);
        }
        else
        {
            std::cerr << error << std::endl;
        }
    }

    std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
    wif.imbue(loc);

    std::wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}

}   // framework