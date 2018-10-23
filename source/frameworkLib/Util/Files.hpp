#pragma once

#include <string>

namespace framework
{

std::string loadTextFromFile(const std::string& filePath, bool throws = false);
std::wstring loadTextFromUtf8File(const std::string& filePath, bool throws = false);

}