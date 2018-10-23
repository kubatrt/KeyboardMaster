#include "ResourceHolder.hpp"

namespace framework
{

ResourceHolder& ResourceHolder::get()
{
    static ResourceHolder holder;
    return holder;
}

ResourceHolder::ResourceHolder()
    : fonts("fonts", "ttf")
    , textures("textures", "png")
    , sounds("audio", "wav")
{

}

}