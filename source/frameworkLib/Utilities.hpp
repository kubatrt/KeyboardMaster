#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <cwctype>
#include <random>
#include <sstream>
#include <algorithm>
#include <functional>

#include "Util/NonCopyable.hpp"
#include "Util/NonMoveable.hpp"
#include "Util/Maths.hpp"
#include "Util/Random.hpp"
#include "Util/Files.hpp"

// Debug level: 0 - off, 1 - info,  2 - debug
#define DEBUG_LEVEL 0   

// FIXME: DEPRACTED
#define log_info(msg) if(DEBUG_LEVEL  > 0) std::wcerr << msg << std::endl;
#define log_debug(msg) if(DEBUG_LEVEL > 1) std::wcerr << "(DEBUG): " << msg " ::" << __FILE__ << ":" << __LINE__ << std::endl;

typedef unsigned int uint;
using WChar = wchar_t;
using WStr = std::wstring;
using FilePath = std::string;


namespace framework
{

std::vector<std::string> getLinesFromText(const std::string& text);

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
		str.erase(std::remove_if(str.begin(), str.end(), std::bind(std::isspace<char>, _1, std::locale::classic())), str.end());
	}

	void operator()(std::wstring& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(), std::bind(std::isspace<wchar_t>, _1, std::locale::classic())), str.end());
	}
};

} // charutils


template <typename T>
void printVec(std::ostream& out, T vec)
{
	out << "[" << vec.x << ", " << vec.y << "]";
}

// print variadic argument pack
template <typename... Args>
void printVA(std::ostream& out, Args&&... args)
{
	out << "[";
    using expander = int[];
	(void)expander { (void(out << ' ' << std::forward<Args>(args)),0)... };
	out << "]";
}

} // framework
