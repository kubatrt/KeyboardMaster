#pragma once

#include <SFML/Graphics.hpp>

namespace km
{

using AssetName = std::string;

enum KeyCode : uint
{
    // UTF-8 unicode, decimal values
    EOL = 0,
    Backspace = 8,
    Enter = 13,
    Space = 32,
    q = 113,
    w = 119,
    e = 101,
    r = 114,
    t = 116,
    y = 121,
    u = 117,
    i = 105,
    o = 111,
    p = 112,
    bracketL = 91,
    bracketR = 93,
    backslash = 92,
    a = 97,
    s = 115,
    d = 100,
    f = 102,
    g = 103,
    h = 104,
    j = 106,
    k = 107,
    l = 108,
    semicolon = 59,
    apostrophe = 39,
    z = 122,
    x = 120,
    c = 99,
    v = 118,
    b = 98,
    n = 110,
    m = 109,
    comma = 44,
    dot = 46,
    slash = 47,
	A = 65, // A + 32 = a
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90
	// Ź = 377
	// ź = 378
	// Ź = 379
	// ż = 380
	// Ą = 260
	// ą = 261
	// Ć = 262
	// ć = 263
	// Ę = 280
	// ę = 281
	// Ł = 321
	// ł = 322
	// Ó = 211
	// ó = 243
	// Ń = 323
	// ń = 324
};



namespace experimental
{

class Entity
{
public:
    void setVelocity(sf::Vector2f v) { velocity_ = v; }
    sf::Vector2f getVelocity() const { return velocity_; }
private:
    sf::Vector2f velocity_;
};


struct ILetterTyped
{
	virtual ~ILetterTyped() = default;
    virtual void typedLetter(const wchar_t letter) = 0;
};

struct IWordTyped
{
	virtual ~IWordTyped() = default;
    virtual void typedWord(const std::wstring word) = 0;
};

// Collision: check intersection with two rectangle shapes
template<typename T1, typename T2>
bool isIntersecting(T1& a, T2& b)
{
    return  a.right() >= b.left() && a.left() <= b.right()
        && a.top() <= b.bottom() && a.bottom() >= b.top();
}

enum class ECourseLevel : unsigned
{
    ECourseLevel_1 = 1,
    ECourseLevel_2 = 2,
    ECourseLevel_3 = 3,
    ECourseLevel_4 = 4,
    ECourseLevel_5 = 5
};

struct User
{
    std::string name;
    ECourseLevel courseLevel;   // 0 - 20 deterimnes players skill level
};


struct Session
{
    Session() noexcept {};
    ~Session() = default;

    User user;
    sf::Time timeStarted;
    std::string saveFilePath;

    void save();
    void load();
};


struct GameSession
{
    int score;
    int lives;
    float time;
};


// player game representative object
struct PlayerSpaceShip
{
    sf::Sprite  sprite;
    // animation
    // moving
    // tween position
};

} // experimental

} // namespace km
