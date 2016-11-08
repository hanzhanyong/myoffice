#include "moAnalyse.h"
#include "../Common/moVec.h"
#include "../Common/moMath.h"

using namespace MyOffice;
using namespace MyOffice::DB;
using namespace MyOffice::Analyse;

MoDataSource *MoAnalyse::autoCal(
	DB::MoRoom* room, 
	DB::MoDoor* door, 
	int roomQTCount,		/*前台*/
	int roomHYCount,		/*会议室*/
	int roomOfficeCount		/*办公室*/)
{
	MoDataSource *dataSource = room->getDataSource();

	//先不要考虑结果的方案
	/*
	1.	前台区域计算（规格大小的前台区域）

		入户门口所在墙线的一半，是否小于前台区域短边
		是，整个墙线作为前台区域的短边
		否，计算入户门到所在墙线的左右顶点位置的距离，取距离短的顶点P
		判定前台的长边是否小于门到墙线顶点P距离的一半
		是，前台区域的应以门为中心，向两边延伸
		否，前台区域应以墙线顶点P向门口位置延伸
		计算前台区域的垂直门口所在墙线的另外两坐标点

		垂直方向有墙边的，判断墙边的长度是否比规定的前台边长大
		大，直接添加墙的顶点
		小，墙的顶点应包含在前台区域边线内，添加延伸顶点
		或者直接到墙的顶点位置即可
	*/
	MoRoomRect *receptionRoom = new MoRoomRect();
	receptionRoom->setRoomType(MoRoomRect::RT_MEDIUM);

	MoVertex *alignVertex = door->alignInfo1Vertex();
	MoLine *doorLine = room->getLine(alignVertex->getSeqNo());

	if (doorLine->length() / 2.0 < receptionRoom->width())
	{
		MoLine *doorLineNext = room->getLine(alignVertex->getNextSeqNo());
		MoLine *doorLinePre = room->getLine(alignVertex->getPreSeqNo());
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
		MoVertex *vlineNext = NULL;
		MoVertex *vlinePre = NULL;
		//1
		if (doorLineNext->length() / 2.0 > receptionRoom->length())
		{
			//2
			Vec3f ptUnit = *doorLineNext->start()- *doorLineNext->end();
			ptUnit.normalize();
			Vec3f pt = *doorLineNext->end() + ptUnit * receptionRoom->length();
			vlineNext = dataSource->createVertex(pt.x(), pt.y());
		}

		if (vlineNext == NULL)
		{
			//3
			if (doorLineNext->length() > receptionRoom->length()/2)
			{
				//4
				vlineNext = doorLineNext->start();
			}
			else
			{
				//5
				Vec3f ptUnit = *doorLineNext->start() - *doorLineNext->end();
				ptUnit.normalize();
				Vec3f pt = *doorLineNext->end() + ptUnit * receptionRoom->length();
				vlineNext = dataSource->createVertex(pt.x(), pt.y());
			}
		}


		//1
		if (doorLinePre->length() / 2.0 > receptionRoom->length())
		{
			//2
			Vec3f ptUnit = *doorLinePre->end() - *doorLinePre->start();
			ptUnit.normalize();
			Vec3f pt = *doorLinePre->start() + ptUnit * receptionRoom->length();
			vlinePre = dataSource->createVertex(pt.x(), pt.y());
		}

		if (vlinePre == NULL)
		{
			//3
			if (doorLinePre->length() > receptionRoom->length() / 2)
			{
				//4
				vlinePre = doorLinePre->end();
			}
			else
			{
				//5
				Vec3f ptUnit = *doorLinePre->end() - *doorLinePre->start();
				ptUnit.normalize();
				Vec3f pt = *doorLinePre->start() + ptUnit * receptionRoom->length();
				vlinePre = dataSource->createVertex(pt.x(), pt.y());
			}
		}

		//6
		printf("len1=%f   len2=%f", (*vlineNext - *doorLine->start()).length(), (*vlinePre - *doorLine->end()).length());
		if ((*vlineNext - *doorLine->start()).length() > 1.0 + (*vlinePre - *doorLine->end()).length())
		{
			//7
			Vec3f ptUnit = *vlinePre - *doorLine->end();
			ptUnit.normalize();
			Vec3f pt = *doorLine->end() + ptUnit * (*vlineNext - *doorLine->start()).length();
			vlinePre = dataSource->createVertex(pt.x(), pt.y());
		}
		else if ((*vlineNext - *doorLine->start()).length()+1.0 < (*vlinePre - *doorLine->end()).length())
		{
			//7
			Vec3f ptUnit = *vlineNext - *doorLine->start();
			ptUnit.normalize();
			Vec3f pt = *doorLine->start() + ptUnit * (*vlinePre - *doorLine->end()).length();
			vlineNext = dataSource->createVertex(pt.x(), pt.y());
		}

		//8
		dataSource->add(vlinePre);
		dataSource->add(vlineNext);
		receptionRoom->addVertex(doorLine->start());
		receptionRoom->addVertex(doorLine->end());
		receptionRoom->addVertex(vlinePre);
		receptionRoom->addVertex(vlineNext);
		receptionRoom->setStartVSeqNo(doorLine->start()->getSeqNo());
		dataSource->add(receptionRoom);

		
		//10
		
		if (doorLineNext->start() != vlineNext)
		{
			vlineNext = dataSource->createVertex(vlineNext->x(), vlineNext->y());//重现复制一个点给room使用
			dataSource->add(vlineNext);

			void*  vobj = room->insertAfterVertex(doorLineNext->start(), vlineNext);
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}
		if (doorLinePre->end() != vlinePre)
		{
			vlinePre = dataSource->createVertex(vlinePre->x(), vlinePre->y());//重现复制一个点给room使用
			dataSource->add(vlinePre);
			void*  vobj = room->insertAfterVertex(doorLinePre->start(), vlinePre);
			MoLine *line = (MoLine*)vobj;
			line->setWallFlag(MoLine::WF_INNER);
		}

		//9
		room->removeVertex(doorLine->end());
		room->removeVertex(doorLine->start());
		room->setStartVSeqNo(vlineNext->getSeqNo());
		MoLine *line = room->getLine(vlineNext->getSeqNo());
		line->setWallFlag(MoLine::WF_INNER);
	}

	


	return dataSource;
}