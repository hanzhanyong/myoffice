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

#ifndef MYOFFICEDESIGN_ROOM_H_RH
#define MYOFFICEDESIGN_ROOM_H_RH
#include "moLine.h"
#include "moPolygon.h"
#include "moDoor.h"
namespace MyOffice {
	namespace DB {

		class MO_EXPORT_DLL MoRoom : public MoPolygon
		{
		public://构造函数
			MoRoom(const nlohmann::json &_json = nullptr);
			~MoRoom();

			virtual MoElementType	getShapeType() { return MET_ROOM; }
			virtual MoElement *	    clone();

			enum RoomType
			{
				RT_NONE = 0,//none
				RT_RECEPTION = 1,//前台
				RT_OFFICE = 2,//办公室
				RT_MEETING = 3,//会议室
				RT_ROAD = 4,//通道道路
				RT_VIRTUALROOM = 5,//虚拟办公室房间
				RT_VIRTUALZONE = 6,//虚拟区域
			};

			RoomType				getRoomType() { return m_RoomType; }
			void					setRoomType(RoomType type) { m_RoomType = type; }

			int						getStartVSeqNo();
			void					setStartVSeqNo(int seqNo);

			virtual void			init();
			virtual void			addVertex(MoVertex *vertex);
			virtual void			removeVertex(MoVertex *vertex);
			virtual void*			insertAfterVertex(MoVertex* after, MoVertex *vertexNew);

			unsigned int			getLineCount() { return m_LineArray.size(); }
			MoLine				   *getLineIndex(unsigned int index) { return m_LineArray[index]; }
			MoLine				   *getLine(int vStartSeqNo);//线段的起点坐标Id

			nlohmann::json			&toJson();
		protected:
			std::vector<MoLine*>    m_LineArray;
			RoomType				m_RoomType;
		};
	}
}
#endif

