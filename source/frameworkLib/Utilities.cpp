#include "Utilities.hpp"

namespace framework
{

std::vector<std::string> getLinesFromText(const std::string& text)
{
    std::vector<std::string> lines;

    std::istringstream iss(text);

    if (!text.empty())
    {
        std::string line;
        while (std::getline(iss, line))
        {
            lines.push_back(line);
        }
    }

    return lines;
}

}
