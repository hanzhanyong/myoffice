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

#ifndef MYOFFICEDESIGN_RECT_H_
#define MYOFFICEDESIGN_RECT_H_

#include "moRoom.h"
namespace MyOffice {
	namespace DB {

		class MO_EXPORT_DLL MoRoomRect : public MoRoom
		{
		public://构造函数
			MoRoomRect(const nlohmann::json &_json = nullptr);

		public://属性
			virtual MoElementType	getShapeType() { return MET_RECT; }
			virtual MoElement *	    clone();

			enum RoomSizeType
			{
				RST_LARGE = 1,//大
				RST_MEDIUM = 2,//中
				RST_SMALL = 3,//小
				RST_SMALLSMALL = 4//小小
			};

			RoomSizeType	getRoomSizeType() { return m_RoomSizeType; }
			void			setRoomSizeType(RoomSizeType type);

			float			&width() { return m_Width; }  //表示矩形的宽
			float			&length() { return m_Length; }//表示矩形的长
		private:
			RoomSizeType    m_RoomSizeType;
			float			m_Length;
			float			m_Width;
		};
	}
}
#endif

