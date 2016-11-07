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

#ifndef MYOFFICEDESIGN_ROOM_H_
#define MYOFFICEDESIGN_ROOM_H_
#include "moLine.h"
#include "moPolygon.h"
#include "moDoor.h"
namespace MyOffice {
	namespace DB {

		class MO_EXPORT_DLL MoRoom : public MoPolygon
		{
		public://构造函数
			MoRoom() : MoPolygon()
			{
			}
			~MoRoom()
			{
				MoPolygon::~MoPolygon();
				int sizeLine = getLineCount();
				for (int i = 0; i < sizeLine; i++)
				{
					MoLine *line = m_LineArray.at(i);
					delete line;
					m_LineArray.at(i) = NULL;
				}
				m_LineArray.clear();
			}

		public://属性
			virtual MoShapeType	getShapeType() { return MST_ROOM; }

			unsigned int		 getLineCount() { return m_LineArray.size(); }
			MoLine				*getLine(unsigned int index) { return m_LineArray[index]; }

			virtual void		 addVertex( MoVertex *vertex)
			{
				//标记顺时针记录线段的前后关系
				MoPolygon::addVertex(vertex);

				
				int vertexCount = m_VertexArray.size();
				if (vertexCount == 0)return;

				MoLine* currentLine = new MoLine();
				currentLine->setParrent(this);
				if (vertexCount == 1)
				{
					currentLine->start() = *m_VertexArray.at(vertexCount - 1);
					currentLine->end() = *m_VertexArray.at(vertexCount - 1);
				}
				else
				{
					currentLine->start() = *m_VertexArray.at(vertexCount - 2);
					currentLine->end() = *m_VertexArray.at(vertexCount - 1);

					MoLine* firstLine = NULL;
					MoLine* lastLine = NULL;
					firstLine = m_LineArray.at(0);
					lastLine  = m_LineArray.at(m_LineArray.size()-1);

					firstLine->start() = currentLine->end();
					lastLine->end() = currentLine->start();
				}
				
				m_LineArray.push_back(currentLine);
			}
		protected:
			std::vector<MoLine*> m_LineArray;

		};
	}
}
#endif

