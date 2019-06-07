#pragma once

namespace framework
{

class NonMovable
{
public:
    NonMovable() = default;
    NonMovable& operator = (NonMovable&&) = delete;
    NonMovable(NonMovable&&) = delete;
};

}
