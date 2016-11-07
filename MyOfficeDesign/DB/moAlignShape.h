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

#ifndef MYOFFICEDESIGN_ALIGNSHAPE_H_
#define MYOFFICEDESIGN_ALIGNSHAPE_H_

#include "moShape.h"
#include "moVertex.h"

namespace MyOffice {
	namespace DB {

		class MO_EXPORT_DLL MoAlignShape:public MoShape
		{
		public://构造函数
			MoAlignShape() :
				m_VertexId(0),
				m_Distance(0),
				MoShape()
			{}

		public://属性
			int					getAlignVertexId() { return m_VertexId; }
			void				setAlignVertexId(int _id) { m_VertexId = _id; }

			MoVertex *			getAlignVertex() { return NULL; }

			float				getDistance() { return m_Distance; }
			void				setDistance(float _distance) { m_Distance = _distance; }
		protected:
			int					m_VertexId;
			float				m_Distance;
		};
	}
}
#endif

