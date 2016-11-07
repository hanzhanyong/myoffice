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

#ifndef MYOFFICEDESIGN_VECTOR_H_
#define MYOFFICEDESIGN_VECTOR_H_
#include "moMath.h"
namespace MyOffice {
	template<typename T, int size>
	class TemplateVec
	{
	public:
		T _v[size];

		TemplateVec()
		{
			for (int i = 0; i < size; i++)
				_v[i] = 0.0;
		}
		template<typename TVec>
		TemplateVec(const TVec &v)
		{
			for (int i = 0; i < size; i++)
				_v[i] = v._v[i];
		}
		TemplateVec(T x, T y)
		{
			_v[0] = x;
			_v[1] = y;
		}
		TemplateVec(T x, T y, T z)
		{
			_v[0] = x;
			_v[1] = y;
			if (size > 2)
				_v[2] = z;
		}
		TemplateVec(T x, T y, T z, T w)
		{
			_v[0] = x;
			_v[1] = y;
			if (size > 2)
				_v[2] = z;
			if (size > 3)
				_v[3] = w;
		}

		inline bool operator == (const TemplateVec& v) const
		{
			if (size > 3)
				return  _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2] && _v[3] == v._v[3];
			else if (size > 2)
				return  _v[0] == v._v[0] && _v[1] == v._v[1] && _v[2] == v._v[2];
			else
				return  _v[0] == v._v[0] && _v[1] == v._v[1];
		}
		inline bool operator != (const TemplateVec& v) const
		{
			if (size > 3)
				return  _v[0] != v._v[0] && _v[1] != v._v[1] && _v[2] != v._v[2] && _v[3] != v._v[3];
			else if (size > 2)
				return  _v[0] != v._v[0] && _v[1] != v._v[1] && _v[2] != v._v[2];
			else
				return  _v[0] != v._v[0] && _v[1] != v._v[1];
		}

		inline T * ptr() { return _v; }
		inline const T * ptr() const { return _v; }

		inline void set(T x, T y) { _v[0] = x; _v[1] = y; }
		inline void set(T x, T y, T z) { _v[0] = x; _v[1] = y; _v[2] = z; }
		inline void set(T x, T y, T z, T w) { _v[0] = x; _v[1] = y; _v[2] = z; _v[3] = w; }

		inline T & operator [] (int i) { return _v[i]; }
		inline T operator [] (int i) const { return _v[i]; }

		inline T & x() { return _v[0]; }
		inline T & y() { return _v[1]; }
		inline T & z() { return _v[2]; }
		inline T & w() { return _v[3]; }

		inline T x() const { return _v[0]; }
		inline T y() const { return _v[1]; }
		inline T z() const { return _v[2]; }
		inline T w() const { return _v[3]; }

		inline T & r() { return _v[0]; }
		inline T & g() { return _v[1]; }
		inline T & b() { return _v[2]; }
		inline T & a() { return _v[3]; }

		inline T r() const { return _v[0]; }
		inline T g() const { return _v[1]; }
		inline T b() const { return _v[2]; }
		inline T a() const { return _v[3]; }

		inline bool isValid() const { return !isNaN(); }
		inline bool isNaN() const
		{
			if (size > 3)
				return mapf::isNaN(_v[0]) || mapf::isNaN(_v[1]) || mapf::isNaN(_v[2]) || mapf::isNaN(_v[3]);
			else if (size > 2)
				return mapf::isNaN(_v[0]) || mapf::isNaN(_v[1]) || mapf::isNaN(_v[2]);
			else
				return mapf::isNaN(_v[0]) || mapf::isNaN(_v[1]);
		}

		/** Dot product. */
		inline T operator * (const TemplateVec& rhs) const
		{
			if (size > 3)
				return _v[0] * rhs._v[0] + _v[1] * rhs._v[1] + _v[2] * rhs._v[2] + _v[3] * rhs._v[3];
			else if (size > 2)
				return _v[0] * rhs._v[0] + _v[1] * rhs._v[1] + _v[2] * rhs._v[2];
			else
				return _v[0] * rhs._v[0] + _v[1] * rhs._v[1];
		}

		/** Cross product. */
		inline const TemplateVec operator ^ (const TemplateVec& rhs) const
		{
			return Vec3f(_v[1] * rhs._v[2] - _v[2] * rhs._v[1],
				_v[2] * rhs._v[0] - _v[0] * rhs._v[2],
				_v[0] * rhs._v[1] - _v[1] * rhs._v[0]);
		}

		/** Multiply by scalar. */
		inline const TemplateVec operator * (T rhs) const
		{
			if (size > 3)
				return TemplateVec(_v[0] * rhs, _v[1] * rhs, _v[2] * rhs, _v[3] * rhs);
			else if (size > 2)
				return TemplateVec(_v[0] * rhs, _v[1] * rhs, _v[2] * rhs);
			else
				return TemplateVec(_v[0] * rhs, _v[1] * rhs);
		}

		/** Unary multiply by scalar. */
		inline TemplateVec& operator *= (T rhs)
		{
			_v[0] *= rhs;
			_v[1] *= rhs;
			if (size > 2)_v[2] *= rhs;
			if (size > 3)_v[3] *= rhs;
			return *this;
		}

		/** Divide by scalar. */
		inline const TemplateVec operator / (T rhs) const
		{
			if (size > 3)
				return TemplateVec(_v[0] / rhs, _v[1] / rhs, _v[2] / rhs, _v[3] / rhs);
			else if (size > 2)
				return TemplateVec(_v[0] / rhs, _v[1] / rhs, _v[2] / rhs);
			else
				return TemplateVec(_v[0] / rhs, _v[1] / rhs);
		}

		/** Unary divide by scalar. */
		inline TemplateVec& operator /= (T rhs)
		{
			_v[0] /= rhs;
			_v[1] /= rhs;
			if (size > 2)_v[2] /= rhs;
			if (size > 3)_v[3] /= rhs;
			return *this;
		}

		/** Binary vector add. */
		inline const TemplateVec operator + (const TemplateVec& rhs) const
		{
			if (size > 3)
				return TemplateVec(_v[0] + rhs._v[0], _v[1] + rhs._v[1], _v[2] + rhs._v[2], _v[3] + rhs._v[3]);
			else if (size > 2)
				return TemplateVec(_v[0] + rhs._v[0], _v[1] + rhs._v[1], _v[2] + rhs._v[2]);
			else
				return TemplateVec(_v[0] + rhs._v[0], _v[1] + rhs._v[1]);
		}

		/*
		* Unary vector add. Slightly more efficient because no temporary
		* intermediate object.
		*/
		inline TemplateVec& operator += (const TemplateVec& rhs)
		{
			_v[0] += rhs._v[0];
			_v[1] += rhs._v[1];
			if (size > 2)_v[2] += rhs;
			if (size > 3)_v[3] += rhs;
			return *this;
		}

		/** Binary vector subtract. */
		inline const TemplateVec operator - (const TemplateVec& rhs) const
		{
			if (size > 3)
				return TemplateVec(_v[0] - rhs._v[0], _v[1] - rhs._v[1], _v[2] - rhs._v[2], _v[3] - rhs._v[3]);
			else if (size > 2)
				return TemplateVec(_v[0] - rhs._v[0], _v[1] - rhs._v[1], _v[2] - rhs._v[2]);
			else
				return TemplateVec(_v[0] - rhs._v[0], _v[1] - rhs._v[1]);
		}

		/** Unary vector subtract. */
		inline TemplateVec& operator -= (const TemplateVec& rhs)
		{
			_v[0] -= rhs._v[0];
			_v[1] -= rhs._v[1];
			if (size > 2)_v[2] -= rhs;
			if (size > 3)_v[3] -= rhs;
			return *this;
		}

		/** Negation operator. Returns the negative of the TemplateVec. */
		inline const TemplateVec operator - () const
		{
			if (size > 3)
				return TemplateVec(-_v[0], -_v[1], -_v[2], -_v[3]);
			else if (size > 2)
				return TemplateVec(-_v[0], -_v[1], -_v[2]);
			else
				return TemplateVec(-_v[0], -_v[1]);
		}

		/** Length of the vector = sqrt( vec . vec ) */
		inline T length() const
		{
			if (size > 2)
				return sqrtf(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);
			else
				return sqrtf(_v[0] * _v[0] + _v[1] * _v[1]);
		}

		/** Length squared of the vector = vec . vec */
		inline T length2(void) const
		{
			return _v[0] * _v[0] + _v[1] * _v[1];
		}

		/*
		* Normalize the vector so that it has length unity.
		* Returns the previous length of the vector.
		*/
		inline T normalize()
		{
			T norm = TemplateVec::length();
			if (norm > 0.0)
			{
				double inValue = 1.0f / norm;
				_v[0] *= inValue;
				_v[1] *= inValue;
				if (size > 2)_v[2] *= inValue;
			}
			return(norm);
		}

	};
	typedef TemplateVec<int, 2>			Vec2i;
	typedef TemplateVec<float, 2>		Vec2f;
	typedef TemplateVec<double, 2>		Vec2d;
	typedef TemplateVec<int, 3>			Vec3i;
	typedef TemplateVec<float, 3>		Vec3f;
	typedef TemplateVec<double, 3>		Vec3d;
	typedef TemplateVec<int, 4>			Vec4i;
	typedef TemplateVec<float, 4>		Vec4f;
	typedef TemplateVec<double, 4>      Vec4d;
}
#endif

