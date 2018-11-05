#pragma once

#include <random>
#include <ctime>
#include <chrono>

namespace framework
{

struct RandomMachine
{
    template<class T>
    static T getRange(T min, T max)
    {
        std::random_device rd;
        std::default_random_engine re(rd()); //std::mt19937

        // use epoch time as seed for random generator
        long int seed = static_cast<long int>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now().time_since_epoch()).count());
        re.seed(seed);
        std::uniform_int_distribution<T> unif_dist_wordlength(min, max);

        return unif_dist_wordlength(re);
    }
};

// new Random generator helper class
template <typename Engine = std::mt19937>
class Random
{
    template<typename T>
    using UniformDist = std::uniform_real_distribution<T>;
    using UniformIntDist = std::uniform_int_distribution<int>;

    public:
        Random(int seed = std::time(nullptr))
        	: m_prng(seed)
        {}

        int getIntInRange(int low, int high)
        {
            return getNumberInRange<UniformIntDist>(low, high);
        }

        float getFloatInRange(float low, float high)
        {
            return getNumberInRange<UniformDist<float>>(low, high);
        }

        template<typename T>
        T getNumberInRange(T low, T high)
        {
            return getNumberInRange<UniformDist<T>>(low, high);
        }

        template<typename Dist, typename T>
        T getNumberInRange(T low, T high)
        {
            Dist dist(low, high);
            return dist(m_prng);
        }

    private:
        Engine m_prng;
};

}
