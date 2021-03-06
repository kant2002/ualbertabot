#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <cstdlib>

#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <array>
#include <memory>
#include <limits>

#pragma warning( push )
#pragma warning( disable : 4458)
#include <BWAPI/Position.h>
#pragma warning( pop )

#include "UABAssert.h"

#define UALBERTABOT_PROJECT

struct double2
{
	double x,y;

	double2() noexcept : x(0), y(0) {}
	double2(double x, double y) noexcept : x(x), y(y) {}
	double2(const BWAPI::Position & p) noexcept : x(p.x), y(p.y) {}

	operator BWAPI::Position()				const { return BWAPI::Position(static_cast<int>(x),static_cast<int>(y)); }

	double2 operator + (const double2 & v)	const noexcept { return double2(x+v.x,y+v.y); }
	double2 operator - (const double2 & v)	const noexcept { return double2(x-v.x,y-v.y); }
	double2 operator * (double s)			const noexcept { return double2(x*s,y*s); }
	double2 operator / (double s)			const noexcept { return double2(x/s,y/s); }

	double dot(const double2 & v)			const noexcept { return x*v.x + y*v.y; }
	double lenSq()							const noexcept { return x*x + y*y; }
	double len()							const { return sqrt(lenSq()); }
	double2 normal()						const { return *this / len(); }

	void normalise() { double s = len(); x/=s; y/=s; } 
	void rotate(double angle) noexcept
	{ 	
		angle = angle*M_PI/180.0;
		*this = double2(x * cos(angle) - y * sin(angle), y * cos(angle) + x * sin(angle));
	}
};

struct Rect
{
    int x, y;
    int height, width;
};

using std::shared_ptr;
using std::unique_ptr;
