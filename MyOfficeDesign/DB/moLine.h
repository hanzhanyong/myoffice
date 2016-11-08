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

#ifndef MYOFFICEDESIGN_LINE_H_
#define MYOFFICEDESIGN_LINE_H_

#include "moVertex.h"
namespace MyOffice {
	namespace DB {

		class MO_EXPORT_DLL MoLine : public MoElement
		{
		public://构造函数
			MoLine() :
				m_StartVertex(NULL), 
				m_EndVertex(NULL), 
				m_Parrent(NULL), 
				m_WallFlag(WF_OUTER),
				MoElement() {}

			enum WallFlag
			{
				WF_INNER,
				WF_OUTER
			};
		public://属性
			virtual MoElementType	getShapeType() { return MET_LINE; }

			WallFlag				getWallFlag() { return m_WallFlag; }
			void					setWallFlag(WallFlag wallflag) { m_WallFlag = wallflag; }

			MoVertex				*start() { return m_StartVertex; }
			MoVertex				*end() { return m_EndVertex; }
			void					setStart(MoVertex *v) { m_StartVertex = v; }
			void					setEnd(MoVertex *v) { m_EndVertex = v; }
			float					length() { return (*m_EndVertex - *m_StartVertex).length(); }

			MoShape*				getParrent() { return m_Parrent; }
			void					setParrent(MoShape *shape) { m_Parrent = shape; }
		protected:
			MoVertex				*m_StartVertex;
			MoVertex				*m_EndVertex;

			MoShape					*m_Parrent;
			WallFlag				 m_WallFlag;
		};
	}
}
#endif

