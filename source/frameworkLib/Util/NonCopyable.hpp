#pragma once

namespace framework
{

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable& operator = (const NonCopyable&) = delete;
    NonCopyable(const NonCopyable&) = delete;
};

}