#pragma once

namespace framework 
{

constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;


template <typename T>
T toRadians(T degrees)
{
    return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
    return (radians * 180) / PI;
}

struct Point
{
	int x;
	int y;

	Point(int _x, int _y) : x(_x), y(_y) {}
};

struct Rect
{
	int x;
	int y;
	int width;
	int height;

	Rect(int _x, int _y, int _width, int _height)
		: x(_x), y(_y), width(_width), height(_height)
	{
	}
};


template <typename TPoint, typename TRect>
bool collision2d(TPoint a, TRect b)
{
	return ((a.x >= b.x && a.y >= b.y)
		&& (a.x < b.width && a.y < b.height));
}

// power
template <typename T>
T power(T a, unsigned N)
{
	if (N == 0)
		return a;
	return power(a*a, N - 1);
}

template <unsigned N, typename T, bool = (N % 2 == 0)>	// not named bool
struct p
{
	T operator()(T x) { return x * p<N - 1, T>{}(x); }
};

template <unsigned N, typename T>
struct p<N, T, true>
{
	T operator()(T x) { return p<N / 2, T>{}(x * x); }
};

template <unsigned N, typename T>
T power(T x)
{
	return p<N, T>()(x);
}

}