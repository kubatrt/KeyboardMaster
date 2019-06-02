#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <cwctype>
#include <random>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cmath>

#include "Util/Maths.hpp"
#include "Util/Random.hpp"
#include "Util/Files.hpp"
#include "Util/Logger.hpp"


// Global type definitions
typedef unsigned int uint;

using WChar = wchar_t;
using WStr = std::wstring;
using FilePath = std::string;


namespace framework
{

std::vector<std::string> getLinesFromText(const std::string& text);

template <typename T>
T middlePoint(const T& a, const T& b)
{
	T middle;
	middle.x = abs(a.x - b.x) / 2;
	middle.y = abs(a.y - b.y) / 2;
	return middle;
}

template <typename T>
T mirrorPoint(const T& point)
{
	return T(-point.x, -point.y);
}

namespace charutils
{

struct Capitalize
{
    void operator()(std::string &str)
    {
        str[0] = toupper(str[0]);
    }
    void operator()(std::wstring &str)
    {
        str[0] = towupper(str[0]);
    }
};

struct ToUpper
{
	void operator()(std::string &str)
	{
		for (auto& s : str)
		{
			s = toupper(s);
		}
	}
	void operator()(std::wstring &str)
	{
		for (auto& s : str)
		{
			s = towupper(s);
		}
	}
};

struct ToLower
{
	void operator()(std::string &str)
	{
		for (auto& s : str)
		{
			s = tolower(s);
		}
	}
	void operator()(std::wstring &str)
	{
		for (auto& s : str)
		{
			s = towlower(s);
		}
	}
};

using namespace std::placeholders;

struct RemoveSpaces
{
	void operator()(std::string& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), std::bind(std::isspace<char>, _1,
				std::locale::classic())), str.end());
	}

	void operator()(std::wstring& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), std::bind(std::isspace<wchar_t>, _1,
				std::locale::classic())), str.end());
	}
};

}


// Print SFML Vector2 structure
template <typename T>
void printVec(std::ostream& out, T vec)
{
	out << "[" << vec.x << ", " << vec.y << "]";
}

// Print variadic argument pack
template <typename... Args>
void printVA(std::ostream& out, Args&&... args)
{
	out << "[";
    using expander = int[];
	(void)expander { (void(out << ' ' << std::forward<Args>(args)),0)... };
	out << "]";
}

} // framework
