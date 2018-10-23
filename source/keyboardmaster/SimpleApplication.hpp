#pragma once

namespace KM
{

class SimpleApplication
{
public:
    SimpleApplication() = default;
    virtual ~SimpleApplication() = default;

    virtual int run(int argc, char* argv) = 0;
};

}
