/************ C++ ********  MyOfficeDesign Engine (MIT License)   ***********************
************************** Copyright (C) 2014-2016 mapf.cn ***********************
**************************     author:hanzhanyong          ***********************
**************************     email:306679711@qq.com      ***********************
**************************     http://www.mapf.cn          ***********************

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************************/

#ifndef MYOFFICEDESIGN_MATH_H
#define MYOFFICEDESIGN_MATH_H

#include <cmath>
#include <cfloat>

namespace MyOffice {

#ifdef PI
#undef PI
#undef PI_2
#undef PI_4
#undef PI_OVER_180
#undef PI_OVER_360
#endif

	const double PI = 3.14159265358979323846;
	const double PI_2 = 1.57079632679489661923;
	const double PI_4 = 0.78539816339744830962;
	const double PI_8 = 0.39269908169872415481;
	const double LN_2 = 0.69314718055994530942;
	const double INVLN_2 = 1.0 / LN_2;
	const double PI_OVER_180 = 0.017453292519943295769236907684886;
	const double PI_OVER_360 = 0.0087266462599716478846184538424431;

	template<typename T>
	inline T abs(T v) { return v<(T)0 ? -v : v; }

	inline bool equivalent(float lhs, float rhs, float epsilon = 1e-6)
	{
		float delta = rhs - lhs; return delta<0.0f ? delta >= -epsilon : delta <= epsilon;
	}

	inline bool equivalent(double lhs, double rhs, double epsilon = 1e-6)
	{
		double delta = rhs - lhs; return delta<0.0 ? delta >= -epsilon : delta <= epsilon;
	}

	template<typename T>
	inline T min(T lhs, T rhs) { return lhs<rhs ? lhs : rhs; }

	template<typename T>
	inline T max(T lhs, T rhs) { return lhs>rhs ? lhs : rhs; }



	template<typename T>
	inline T clampTo(T v, T minimum, T maximum)
	{
		return v<minimum ? minimum : v>maximum ? maximum : v;
	}

	template<typename T>
	inline T clampAbove(T v, T minimum) { return v<minimum ? minimum : v; }

	template<typename T>
	inline T clampBelow(T v, T maximum) { return v>maximum ? maximum : v; }

	template<typename T>
	inline T clampBetween(T v, T minimum, T maximum)
	{
		return clampBelow(clampAbove(v, minimum), maximum);
	}

	template<typename T>
	inline T sign(T v) { return v<(T)0 ? (T)-1 : (T)1; }

	template<typename T>
	inline T signOrZero(T v) { return v<(T)0 ? (T)-1 : (v>(T)0 ? (T)1 : 0); }

	template<typename T>
	inline T square(T v) { return v*v; }

	template<typename T>
	inline T signedSquare(T v) { return v<(T)0 ? -v*v : v*v; }



	inline float inDegrees(float angle) { return angle*(float)PI / 180.0f; }
	inline double inDegrees(double angle) { return angle*PI / 180.0; }

	template<typename T>
	inline T inRadians(T angle) { return angle; }

	inline float DegreesToRadians(float angle) { return angle*(float)PI / 180.0f; }
	inline double DegreesToRadians(double angle) { return angle*PI / 180.0; }

	inline float RadiansToDegrees(float angle) { return angle*180.0f / (float)PI; }
	inline double RadiansToDegrees(double angle) { return angle*180.0 / PI; }

	inline float round(float v) { return v >= 0.0f ? floorf(v + 0.5f) : ceilf(v - 0.5f); }
	inline double round(double v) { return v >= 0.0 ? floor(v + 0.5) : ceil(v - 0.5); }

#if defined(_WIN32) && !defined(__CYGWIN__) && !defined(__MWERKS__)
	inline bool isNaN(float v) { return _isnan(v) != 0; }
	inline bool isNaN(double v) { return _isnan(v) != 0; }
#else
#if defined(__APPLE__)
	inline bool isNaN(float v) { return isnan(v); }
	inline bool isNaN(double v) { return isnan(v); }
#else
	// Need to use to std::isnan to avoid undef problem from <cmath>
	inline bool isNaN(float v) { return isnan(v); }
	inline bool isNaN(double v) { return isnan(v); }
#endif
#endif


	/** compute the volume of a tetrahedron. */
	template<typename T>
	inline float computeVolume(const T& a, const T& b, const T& c, const T& d)
	{
		return fabsf(((b - c) ^ (a - b))*(d - b));
	}

	/** compute the volume of a prism. */
	template<typename T>
	inline float computeVolume(const T& f1, const T& f2, const T& f3,
		const T& b1, const T& b2, const T& b3)
	{
		return computeVolume(f1, f2, f3, b1) +
			computeVolume(b1, b2, b3, f2) +
			computeVolume(b1, b3, f2, f3);
	}

	/** Convert a ascii number to a double float, ignoring locale settings.*/
	extern double asciiToDouble(const char* str);

	/** Convert a ascii number to a float, ignoring locale settings.*/
	inline float asciiToFloat(const char* str) { return static_cast<float>(asciiToDouble(str)); }

	/** Detect first ascii POSITIVE number in string and convert to double.*/
	extern double findAsciiToDouble(const char* str);

	/** Detect first ascii POSITIVE number in string and convert to double.*/
	inline float findAsciiToFloat(const char* str) { return static_cast<float>(findAsciiToDouble(str)); }
}
#endif

