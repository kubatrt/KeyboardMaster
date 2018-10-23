#pragma once

namespace framework
{

struct NonMovable
{
    NonMovable() = default;
    NonMovable& operator = (NonMovable&&) = delete;
    NonMovable(NonMovable&&) = delete;
};

}