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

#ifndef MYOFFICEDESIGN_DOOR_H_
#define MYOFFICEDESIGN_DOOR_H_

#include "moAlignShape.h"
namespace MyOffice {
	namespace DB {

		class MO_EXPORT_DLL MoDoor : public MoAlignShape
		{
		public://构造函数
			MoDoor() : MoAlignShape()
			{
				
			}

		public://属性
			virtual MoShapeType	getShapeType() { return MST_DOOR; }

			MoVertex    getLocation()
			{
				
			}

			float		getLength() { return m_Length; }
			void		setLength(float len) { m_Length = len; }

			float		getWidth() { return m_Width; }
			void		setWidth(float w) { m_Width = w; }

			float		getHeight() { return m_Height; }
			void		setHeight(float h) { m_Height = h; }
		private:
			float		m_Length;
			float       m_Width;
			
			float		m_Height;
		};
	}
}
#endif

