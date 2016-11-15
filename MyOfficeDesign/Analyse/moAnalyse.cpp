#include "moAnalyse.h"
#include "moAnalyseResult.h"

#include "../Common/moVec.h"
#include "../Common/moMath.h"
#include "../Common/moMatrix.h"

#include "../DB/moDoor.h"
#include "../DB/moRoom.h"
#include "../DB/moRoomRect.h"
#include "../DB/moDataSource.h"

using namespace MyOffice;
using namespace MyOffice::DB;
using namespace MyOffice::Analyse;
/*
	1、方案的管理（datasource）
	2、前台区域的计算，切割剩余区域
	3、办公室区域的计算，切割剩余区域
	4、前台、办公室门口位置计算
	5、连通前台、办公室的主道路计算（最短路径，线是横竖连接），多条主要道路
	6、使用主道路切割多个剩余区域
	7、会议室区域计算，（由近及远计算剩余区域是否适合会议室），切割剩余区域
*/

MoAnalyseResult *MoAnalyse::autoAnalyse(
	DB::MoDataSource *dataSource,
	int roomQTCount,		/*前台*/
	int roomHYCount,		/*会议室*/
	int roomOfficeCount		/*办公室*/)
{
	MoAnalyseResult *result = new MoAnalyseResult();
	result->addDataSource(dataSource);

	calReceptionRoom(result,roomQTCount);
	calOfficeRoom(result, roomOfficeCount);
	calDoorOfRoom(result);
	calMailRoad(result);
	calCutZone(result);
	calMeetingRoom(result);
	adjustData(result);

	return result;
}


//1 前台区域计算
void MoAnalyse::calReceptionRoom(MoAnalyseResult *result, int num)
{
	if (num == 0)return;
	if (result->getDataSourceCount() == 0)return;

	//获取不包含此RoomType的数据源
	MoDataSource *ds = result->getValidAnalyzeDS(MoRoom::RT_RECEPTION);
	while (ds)
	{
		calReceptionRoom(ds, num);
		ds = result->getValidAnalyzeDS(MoRoom::RT_RECEPTION);
	}
}
void MoAnalyse::calReceptionRoom(MoDataSource *dataSource, int num)
{
	DB::MoRoom* room = dataSource->getRoomIndex(0);
	MyOffice::DB::MoDoor *door = dataSource->getDoorOnRoom(room);
	//先不要考虑结果的方案
	/*
	1.	前台区域计算（规格大小的前台区域）

	入户门口所在墙线的一半，是否小于前台区域短边
	是，整个墙线作为前台区域的短边
	否，计算入户门到所在墙线的左右顶点位置的距离，取距离短的顶点P
	判定前台的长边是否小于门到墙线顶点P距离的一半
	是，前台区域的应以门为中心，向两边延伸
	否，前台区域应以墙线顶点P向门口位置延伸
	计算前台区域的垂直门口所在墙线的另外两坐标点

	垂直方向有墙边的，判断墙边的长度是否比规定的前台边长大
	大，直接添加墙的顶点
	小，墙的顶点应包含在前台区域边线内，添加延伸顶点
	或者直接到墙的顶点位置即可
	*/
	MoRoomRect *receptionRoom = new MoRoomRect();
	receptionRoom->setRoomType(MoRoom::RT_RECEPTION);
	receptionRoom->setRoomSizeType(MoRoomRect::RST_MEDIUM);

	MoVertex *alignVertex = door->alignInfo1Vertex();
	MoLine *doorLine = room->getLine(alignVertex->getSeqNo());
	MoLine *doorLineNext = room->getLine(alignVertex->getNextSeqNo());
	MoLine *doorLinePre = room->getLine(alignVertex->getPreSeqNo());

	MoVertex *vReceptionRoomNext = NULL;
	MoVertex *vReceptionRoomPre = NULL;
	MoVertex *vReceptionRoomNext_Bottom = NULL;
	MoVertex *vReceptionRoomPre_Bottom = NULL;

	if (doorLine->length() / 2.0 < receptionRoom->width())
	{
		/*
		1判断线段的长度的二分之一是否比前台房间的长度大
		2是，直接在线段上添加添加顶点
		3否，判断线段的长度是否比前台的长度二分之一大
		4	是，这根线段的另一端作为前台的一个端点
		5	否，在这根线段的沿线上添加顶点，距离长度为前台房间的长度
		6判断这新添加的两个端点，是否跟门所在线段平行
		7不平行，以距离长的为依据，修补另一个顶点位置
		8修正romm的坐标点，添加前台面
		9 room移除所在门线段的两端点
		10 room添加内墙线1-3边，标记为内墙线
		*/

		//1
		if (doorLineNext->length() / 2.0 > receptionRoom->length())
		{
			//2
			Vec3f ptUnit = *doorLineNext->start() - *doorLineNext->end();
			ptUnit.normalize();
			Vec3f pt = *doorLineNext->end() + ptUnit * receptionRoom->length();
			vReceptionRoomNext = dataSource->createVertex(pt.x(), pt.y());
		}

		if (vReceptionRoomNext == NULL)
		{
			//3
			if (doorLineNext->length() > receptionRoom->length() / 2)
			{
				//4
				vReceptionRoomNext = doorLineNext->start();
			}
			else
			{
				//5
				Vec3f ptUnit = *doorLineNext->start() - *doorLineNext->end();
				ptUnit.normalize();
				Vec3f pt = *doorLineNext->end() + ptUnit * receptionRoom->length();
				vReceptionRoomNext = dataSource->createVertex(pt.x(), pt.y());
			}
		}


		//1
		if (doorLinePre->length() / 2.0 > receptionRoom->length())
		{
			//2
			Vec3f ptUnit = *doorLinePre->end() - *doorLinePre->start();
			ptUnit.normalize();
			Vec3f pt = *doorLinePre->start() + ptUnit * receptionRoom->length();
			vReceptionRoomPre = dataSource->createVertex(pt.x(), pt.y());
		}

		if (vReceptionRoomPre == NULL)
		{
			//3
			if (doorLinePre->length() > receptionRoom->length() / 2)
			{
				//4
				vReceptionRoomPre = doorLinePre->end();
			}
			else
			{
				//5
				Vec3f ptUnit = *doorLinePre->end() - *doorLinePre->start();
				ptUnit.normalize();
				Vec3f pt = *doorLinePre->start() + ptUnit * receptionRoom->length();
				vReceptionRoomPre = dataSource->createVertex(pt.x(), pt.y());
			}
		}

		//6
		//printf("len1=%f   len2=%f", (*vReceptionRoomNext - *doorLine->start()).length(), (*vReceptionRoomPre - *doorLine->end()).length());
		if ((*vReceptionRoomNext - *doorLine->start()).length() > 1.0 + (*vReceptionRoomPre - *doorLine->end()).length())
		{
			//7
			Vec3f ptUnit = *vReceptionRoomPre - *doorLine->end();
			ptUnit.normalize();
			Vec3f pt = *doorLine->end() + ptUnit * (*vReceptionRoomNext - *doorLine->start()).length();
			vReceptionRoomPre = dataSource->createVertex(pt.x(), pt.y());
		}
		else if ((*vReceptionRoomNext - *doorLine->start()).length() + 1.0 < (*vReceptionRoomPre - *doorLine->end()).length())
		{
			//7
			Vec3f ptUnit = *vReceptionRoomNext - *doorLine->start();
			ptUnit.normalize();
			Vec3f pt = *doorLine->start() + ptUnit * (*vReceptionRoomPre - *doorLine->end()).length();
			vReceptionRoomNext = dataSource->createVertex(pt.x(), pt.y());
		}

		//8
		if (vReceptionRoomPre->getPreSeqNo() == -1)dataSource->add(vReceptionRoomPre);
		if (vReceptionRoomNext->getPreSeqNo() == -1)dataSource->add(vReceptionRoomNext);
		receptionRoom->addVertex(doorLine->start());
		receptionRoom->addVertex(doorLine->end());
		if (doorLinePre->end() == vReceptionRoomPre)//同边线共用点，需要复制一份给新的房间使用
		{
			MoVertex *vertex = dataSource->createVertex(vReceptionRoomPre->x(), vReceptionRoomPre->y());
			dataSource->add(vertex);
			receptionRoom->addVertex(vertex);
		}
		else
			receptionRoom->addVertex(vReceptionRoomPre);
		if (doorLineNext->start() == vReceptionRoomNext)//同边线共用点，需要复制一份给新的房间使用
		{
			MoVertex *vertex = dataSource->createVertex(vReceptionRoomNext->x(), vReceptionRoomNext->y());
			dataSource->add(vertex);
			receptionRoom->addVertex(vertex);
		}
		else
			receptionRoom->addVertex(vReceptionRoomNext);
		receptionRoom->setStartVSeqNo(doorLine->start()->getSeqNo());
		dataSource->add(receptionRoom);


		//10

		if (doorLineNext->start() != vReceptionRoomNext)
		{
			vReceptionRoomNext = dataSource->createVertex(vReceptionRoomNext->x(), vReceptionRoomNext->y());//重现复制一个点给room使用
			dataSource->add(vReceptionRoomNext);

			void*  vobj = room->insertAfterVertex(doorLineNext->start(), vReceptionRoomNext);
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}
		if (doorLinePre->end() != vReceptionRoomPre)
		{
			vReceptionRoomPre = dataSource->createVertex(vReceptionRoomPre->x(), vReceptionRoomPre->y());//重现复制一个点给room使用
			dataSource->add(vReceptionRoomPre);
			void*  vobj = room->insertAfterVertex(doorLinePre->start(), vReceptionRoomPre);
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}

		//9
		room->removeVertex(doorLine->end());
		room->removeVertex(doorLine->start());
		room->setStartVSeqNo(vReceptionRoomNext->getSeqNo());
		MoLine *line = room->getLine(vReceptionRoomNext->getSeqNo());
		line->setWallFlag(MoLine::WF_INNER);
	}
	else
	{
		/*  计算前台所在墙线很长的情况

		1 判断入户门距右墙面的距离是否比前台的宽度小
		2	是，直接在右面的墙线段上添加顶点
		3	否，判断入户门距左墙面的距离是否比前台的宽度小
		4		是，直接在左面的墙线段上添加顶点
		5		否，以入户门中心点向所在墙线两面延伸，两段距离都为前台宽度的一半
		6 计算垂直点坐标，判断左右墙线的距离是否比前台的长度的1.5倍小
		7 是，以左右墙线的另一个端点作为前台的一个顶点
		8 否，计算垂直于入户门所在墙线的方向的顶点

		9 添加前台
		10修正办公室的顶点坐标，去除包括前台的顶点
		*/

		float curReceptRoomNext = door->alignInfo1()->getX() + door->getWidth() / 2.0 - (receptionRoom->width() / 2.0);
		float curReceptRoomPre = curReceptRoomNext + receptionRoom->width();
		float curVerticalLen = receptionRoom->length();

		//1
		if (door->alignInfo1()->getX() + door->getWidth() < receptionRoom->width())
		{
			//2
			curReceptRoomNext = 0;
			curReceptRoomPre = receptionRoom->width();

			vReceptionRoomNext_Bottom = doorLine->start();

			//6
			if (curVerticalLen*1.5 > doorLineNext->length())
			{
				curVerticalLen = doorLineNext->length();
				//8
				vReceptionRoomNext = doorLineNext->start();
			}
		}
		//3
		else if (doorLine->length() - door->alignInfo1()->getX() < receptionRoom->width())
		{
			//4
			curReceptRoomPre = doorLine->length();
			curReceptRoomNext = curReceptRoomPre - receptionRoom->width();

			vReceptionRoomPre_Bottom = doorLine->end();

			//6
			if (curVerticalLen*1.5 > doorLinePre->length())
			{
				curVerticalLen = doorLinePre->length();
				//8
				vReceptionRoomPre = doorLinePre->end();
			}
		}
		else
		{
			//6
			if (curVerticalLen*1.5 > doorLinePre->length())
			{
				curVerticalLen = doorLinePre->length();
			}
		}


		Matrixf mt;
		mt.makeRotate(DegreesToRadians(90.0f), 0.0f, 0.0f, 1.0f);
		Vec3f ptUnitH = (*doorLine->end()) - (*doorLine->start());
		Vec3f ptUnitV = ptUnitH * mt;
		ptUnitH.normalize();
		ptUnitV.normalize();

		if (vReceptionRoomNext_Bottom == NULL)
		{
			//2
			Vec3f pt = *doorLine->start() + ptUnitH * curReceptRoomNext;
			vReceptionRoomNext_Bottom = dataSource->createVertex(pt.x(), pt.y());
		}

		if (vReceptionRoomPre_Bottom == NULL)
		{
			//4
			Vec3f pt = *doorLine->start() + ptUnitH * curReceptRoomPre;
			vReceptionRoomPre_Bottom = dataSource->createVertex(pt.x(), pt.y());
		}

		if (vReceptionRoomNext == NULL)
		{
			//7
			Vec3f pt = *vReceptionRoomNext_Bottom + ptUnitV * curVerticalLen;
			vReceptionRoomNext = dataSource->createVertex(pt.x(), pt.y());
		}
		if (vReceptionRoomPre == NULL)
		{
			//7
			Vec3f pt = *vReceptionRoomPre_Bottom + ptUnitV * curVerticalLen;
			vReceptionRoomPre = dataSource->createVertex(pt.x(), pt.y());
		}



		//9
		if (vReceptionRoomNext_Bottom->getPreSeqNo() == -1)
			dataSource->add(vReceptionRoomNext_Bottom);
		if (vReceptionRoomPre_Bottom->getPreSeqNo() == -1)
			dataSource->add(vReceptionRoomPre_Bottom);
		if (vReceptionRoomPre->getPreSeqNo() == -1)
			dataSource->add(vReceptionRoomPre);
		if (vReceptionRoomNext->getPreSeqNo() == -1)
			dataSource->add(vReceptionRoomNext);

		if (doorLine->start() == vReceptionRoomNext_Bottom)
		{
			MoVertex *vertex = dataSource->createVertex(vReceptionRoomNext_Bottom->x(), vReceptionRoomNext_Bottom->y());
			dataSource->add(vertex);
			receptionRoom->addVertex(vertex);
		}
		else
			receptionRoom->addVertex(vReceptionRoomNext_Bottom);
		if (doorLine->end() == vReceptionRoomPre_Bottom)
		{
			MoVertex *vertex = dataSource->createVertex(vReceptionRoomPre_Bottom->x(), vReceptionRoomPre_Bottom->y());
			dataSource->add(vertex);
			receptionRoom->addVertex(vertex);
		}
		else
			receptionRoom->addVertex(vReceptionRoomPre_Bottom);
		if (doorLinePre->end() == vReceptionRoomPre)
		{
			MoVertex *vertex = dataSource->createVertex(vReceptionRoomPre->x(), vReceptionRoomPre->y());
			dataSource->add(vertex);
			receptionRoom->addVertex(vertex);
		}
		else
			receptionRoom->addVertex(vReceptionRoomPre);
		if (doorLineNext->start() == vReceptionRoomNext)
		{
			MoVertex *vertex = dataSource->createVertex(vReceptionRoomNext->x(), vReceptionRoomNext->y());
			dataSource->add(vertex);
			receptionRoom->addVertex(vertex);
		}
		else
			receptionRoom->addVertex(vReceptionRoomNext);

		receptionRoom->setStartVSeqNo(-1);
		dataSource->add(receptionRoom);
		//设置入户门临靠点信息
		door->alignInfo1()->setSeqNo(vReceptionRoomNext_Bottom->getSeqNo());
		door->alignInfo1()->setX(door->alignInfo1()->getX() - (*vReceptionRoomNext_Bottom - *doorLine->start()).length());


		//10
		MoVertex *vdoorLineStart = doorLine->start();
		MoVertex *vdoorLineEnd = doorLine->end();
		MoVertex *vdoorLineNext= doorLineNext->start();
		MoVertex *vdoorLinePre = doorLinePre->end();

		if (vdoorLineEnd != vReceptionRoomPre_Bottom)
		{
			vReceptionRoomPre_Bottom = dataSource->createVertex(vReceptionRoomPre_Bottom->x(), vReceptionRoomPre_Bottom->y());//重现复制一个点给room使用
			dataSource->add(vReceptionRoomPre_Bottom);
			void*  vobj = room->insertAfterVertex(vdoorLineStart, vReceptionRoomPre_Bottom);
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}
		//else
		//{
		//	room->removeVertex(vReceptionRoomPre_Bottom);
		//}

		if (vdoorLineStart != vReceptionRoomNext_Bottom)
		{
			vReceptionRoomNext_Bottom = dataSource->createVertex(vReceptionRoomNext_Bottom->x(), vReceptionRoomNext_Bottom->y());//重现复制一个点给room使用
			dataSource->add(vReceptionRoomNext_Bottom);
			void*  vobj = room->insertAfterVertex(vdoorLineStart, vReceptionRoomNext_Bottom);
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}
		/*else
		{
			room->removeVertex(vReceptionRoomNext_Bottom);
			vReceptionRoomNext_Bottom = NULL;
		}*/

		if (vdoorLineNext != vReceptionRoomNext)
		{
			vReceptionRoomNext = dataSource->createVertex(vReceptionRoomNext->x(), vReceptionRoomNext->y());
			dataSource->add(vReceptionRoomNext);
			void*  vobj = NULL;
			vobj = room->insertAfterVertex(vReceptionRoomNext_Bottom, vReceptionRoomNext);
			
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}
		/*else
			room->removeVertex(vReceptionRoomNext);*/

		if (vdoorLinePre != vReceptionRoomPre)
		{
			vReceptionRoomPre = dataSource->createVertex(vReceptionRoomPre->x(), vReceptionRoomPre->y());
			dataSource->add(vReceptionRoomPre);

			void*  vobj = room->insertAfterVertex(vReceptionRoomNext, vReceptionRoomPre);
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}
		else
		{
			room->removeVertex(vReceptionRoomPre);
		}

		if (vdoorLineEnd == vReceptionRoomPre_Bottom)
			room->removeVertex(vReceptionRoomPre_Bottom);
		if (vdoorLineStart == vReceptionRoomNext_Bottom)
			room->removeVertex(vReceptionRoomNext_Bottom);
		if (vdoorLineNext == vReceptionRoomNext)
			room->removeVertex(vReceptionRoomNext);


		room->setStartVSeqNo(-1);
		/*MoLine *line = room->getLine(vReceptionRoomNext->getSeqNo());
		line->setWallFlag(MoLine::WF_INNER);*/
	}
}