#pragma once

#include <SFML\Graphics.hpp>

namespace km
{

enum KeyCode : unsigned int
{
    // UTF-8 unicode
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
    slash = 47
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


class ILetterTyped
{
public:
    virtual void typedLetter(const wchar_t letter) = 0;
};

class IWordTyped
{
public:
    virtual void typedWord(const std::wstring word) = 0;
};

// Check intersection with two shapes
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