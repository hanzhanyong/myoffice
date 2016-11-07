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

#ifndef MYOFFICEDESIGN_SHAPE_H_
#define MYOFFICEDESIGN_SHAPE_H_

#include "../Common/moExport.h"
#include "../3rdParty/nlohmann/json.hpp"

namespace MyOffice {
	namespace DB {

		enum MoShapeType
		{
			MST_NONE = 0,
			MST_VERTEX = 1,//顶点
			MST_LINE = 2,//线段

			MST_POLYGON = 10,//多边形
			MST_RECT = 11,//矩形

			MST_DOOR = 20,//门

			MST_ROOM = 100,//房间
		};

		class MO_EXPORT_DLL MoElement
		{
		public://构造函数
			MoElement()
			{
				static int mo_Globe_Id = 1;
				m_Id = mo_Globe_Id++;
			}
		public://属性
			int					getId() { return m_Id; }
			void				setId(int _id) { m_Id = _id; }

			
			virtual MoShapeType	getShapeType() = 0;
		protected:
			int					m_Id;
		};
		class MO_EXPORT_DLL MoShape:public MoElement
		{
		
		};
	}
}
#endif

