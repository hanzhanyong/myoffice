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

#ifndef MYOFFICEDESIGN_DATASOURCE_H_
#define MYOFFICEDESIGN_DATASOURCE_H_

#include "moLine.h"
#include "moRoom.h"
#include "moDoor.h"
#include <vector>
namespace MyOffice {
	namespace DB {
		class MO_EXPORT_DLL MoLisener
		{
		public:
			virtual void updateShape(MoShape *shape) = 0;
			virtual void removeShape(MoShape *shape) = 0;
		};
		class MO_EXPORT_DLL MoDataSource
		{
		public://构造函数
			MoDataSource(MoLisener *lisener=NULL):
				m_Version(""),
				m_IsCorrected(true),
				m_CurrentRoomSeqNo(0),
				m_CurrentShapeSeqNo(0),
				m_CurrentVertexSeqNo(0),
				m_Lisener(lisener)
			{
			}
			~MoDataSource();

		public:
			void	setLisener(MoLisener *lisener);

			virtual bool open(const char* fileName);
			virtual bool save(const char* fileName);

			MoVertex *   getVertex(int seqNo);
			MoVertex *   createVertex(float x,float y);

			MoRoom		*getRoom(int seqNo);
			MoRoom		*getRoomVertex(int vseqNo);//根据节点获取房间
			MoDoor		*getDoor(int seqNo);

			virtual void add(MoVertex *vertex);
			virtual void add(MoRoom *room);
			virtual void add(MoDoor *door);
		protected:
			virtual bool		 readJson(const char* jsonStr);
			virtual std::string  getJson();
		private:
			std::string				m_Version;
			bool				    m_IsCorrected;
			int					    m_CurrentRoomSeqNo;//当前房间Id编号的最大值
			int						m_CurrentShapeSeqNo;
			int						m_CurrentVertexSeqNo;

			std::vector<MoElement*>	m_VertexArray;
			std::vector<MoElement*>	m_RoomArray;
			std::vector<MoElement*>	m_DoorArray;

			MoLisener				*m_Lisener;

			
		};
	}
}
#endif

