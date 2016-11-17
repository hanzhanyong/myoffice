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

//2 办公室区域计算
void MoAnalyse::calOfficeRoom(MoAnalyseResult *result, int num)
{
	if (num == 0)return;
	if (result->getDataSourceCount() == 0)return;

	//获取不包含此RoomType的数据源
	MoDataSource *ds = result->getValidAnalyzeDS(MoRoom::RT_OFFICE);
	while (ds)
	{
		calOfficeRoom(result,ds, num);
		ds = result->getValidAnalyzeDS(MoRoom::RT_OFFICE);
	}
}
void MoAnalyse::calOfficeRoom(MoAnalyseResult *result, MoDataSource *dataSource, int num, int type/*0表示长边方案   1表示短边方案*/)
{
	
	/*办公室区域计算
	
	//方案一
	1、排序各个顶点，依据由远及近到入户门的距离
	2、依据办公室的个数，计算所有办公室在一条直线上的最长距离
	3、先以最远的顶点，标记是否已经使用
	4、判断相邻两线段，取（长）边作为办公室的墙线的计算依据
	5、比较上步骤2和步骤4两个距离的大小，步骤2是否小于步骤4的距离
	6、是，直接在步骤4墙线排列办公室的区域位置，考虑最后一个办公室是否需要对齐线段的顶点
	7、否，先排列一部分的办公室，剩余的办公室排列到顶点的另外一个墙线上，如果还有剩余进行步骤8
	8、取未标记使用的顶点而且以距离最远，执行算法步骤4
	
	//方案2复制数据源
	4、判断相邻两线段，取（短）边作为办公室的墙线的计算依据
	*/
	
	

	DB::MoRoom* room = NULL;
	unsigned int roomCount = dataSource->getRoomCount();
	for (unsigned int i = 0; i < roomCount; i++)
	{
		room = dataSource->getRoomIndex(i);
		if (room->getRoomType() == MoRoom::RT_NONE)
			break;
	}
	if (room == NULL)return;
	

	MyOffice::DB::MoDoor *door = dataSource->getFirstDoor();
	Vec3f doorPtCenter = door->getLocation(); //*alignVertex + ptUnit*door->alignInfo1()->getX();
	//1  直接插入排序
	std::vector<MoVertex*> vertexArray;
	int vertexCount = room->getVertexCount();
	for (int i = 0; i < vertexCount; i++)
	{
		MoVertex *vertexi = room->getVertex(i);
		if (i == 0)
		{
			vertexArray.push_back(vertexi);
			continue;
		}
		float distancei = (doorPtCenter - *vertexi).length();
		int j = 0;
		int arraySize = vertexArray.size();
		for (j = 0; j<arraySize; j++)
		{
			MoVertex *vertexj = vertexArray[j];
			float distancej = (doorPtCenter - *vertexj).length();
			if (distancej < distancei)
			{
				break;
			}
		}
		vertexArray.insert(vertexArray.begin()+j, vertexi);
	}

	for (int i = 0; i < vertexCount; i++)
	{
		MoVertex *vertexi = vertexArray[i];
		float distancei = (doorPtCenter - *vertexi).length();
		printf("seqId=%d   distance=%f\n", vertexi->getSeqNo(), distancei);
	}

	MoDataSource *dataSourceAnother = NULL;
	if (type < 1)
	{
		dataSourceAnother = dataSource->clone();//方案2 clone
		result->addDataSource(dataSourceAnother);
	}
	//2

	//3
	int curNum = num;
	for (int i = 0; i < vertexCount; i++)
	{
		float length = 0;

		MoVertex *vOffice = vertexArray[i];
		MoVertex *vOfficeTarget = NULL;
		MoVertex *vOfficeTarget2 = NULL;

		//记录所有办公室组合,最外面的四个顶点
		MoVertex *vOfficeStart1 = NULL;
		MoVertex *vOfficeStartV2 = NULL;
		MoVertex *vOfficeEnd1 = NULL;
		MoVertex *vOfficeEndV2 = NULL;

		MoLine * vOfficeLine = room->getLine(vOffice->getSeqNo());
		MoLine * vOfficeLineNext = room->getLine(vOffice->getNextSeqNo());

		//4
		bool bOrder = true;
		if (type == 0)
		{
			if (vOfficeLine->length() > vOfficeLineNext->length())
			{
				length = vOfficeLine->length();
				vOfficeTarget = vOfficeLine->end();
				vOfficeTarget2 = vOfficeLineNext->start();
				bOrder = true;
			}
			else
			{
				length = vOfficeLineNext->length();
				vOfficeTarget = vOfficeLineNext->start();
				vOfficeTarget2 = vOfficeLine->end();
				bOrder = false;
			}
		}
		else
		{
			if (vOfficeLine->length() > vOfficeLineNext->length())
			{
				vOfficeTarget = vOfficeLineNext->start();
				vOfficeTarget2 = vOfficeLine->end();
				length = vOfficeLine->length();
				bOrder = false;
			}
			else
			{

				vOfficeTarget = vOfficeLine->end();
				vOfficeTarget2 = vOfficeLineNext->start();
				length = vOfficeLineNext->length();
				bOrder = true;
			}
		}

		//5

		Matrixf mt;
		if(vOfficeTarget == vOfficeLine->end())
			mt.makeRotate(DegreesToRadians(90.0f), 0.0f, 0.0f, 1.0f);
		else
			mt.makeRotate(DegreesToRadians(-90.0f), 0.0f, 0.0f, 1.0f);
		Vec3f ptUnitH = (*vOfficeTarget) - (*vOffice);
		Vec3f ptUnitV = ptUnitH * mt;
		ptUnitH.normalize();
		ptUnitV.normalize();

		//6  7
		Vec3f pt;
		int iOffice = 0;
		for (iOffice = 0; iOffice < curNum; iOffice++)
		{
			bool bfinish = false;
			MoRoomRect *officeRoom = new MoRoomRect();
			officeRoom->setRoomType(MoRoom::RT_OFFICE);
			officeRoom->setRoomSizeType(MoRoomRect::RST_MEDIUM);

			MoVertex *vStart = NULL;
			MoVertex *vStart2 = NULL;
			MoVertex *vStartVertical = NULL;
			MoVertex *vStartVertical2 = NULL;
			if (iOffice == 0)
			{
				vStart = vOffice;
				vOfficeStart1 = vStart;
			}
			else
			{
				pt = *vOffice + ptUnitH * (officeRoom->width()*iOffice);
				vStart = dataSource->createVertex(pt.x(), pt.y());
				dataSource->add(vStart);
			}

			pt = *vStart + ptUnitV * officeRoom->length();
			vStartVertical = dataSource->createVertex(pt.x(), pt.y());
			dataSource->add(vStartVertical);
			if (iOffice == 0)vOfficeStartV2 = vStartVertical;

			if (length - officeRoom->width()*(iOffice + 2) < 0)//整个墙线都做办公室情况
			{
				bfinish = true;
				vStart2 = vOfficeTarget;

				pt = *vStartVertical + ptUnitH * officeRoom->width();
				vStartVertical2 = dataSource->createVertex(pt.x(), pt.y());
				dataSource->add(vStartVertical2);				
			}
			else
			{
				pt = *vStart + ptUnitH * officeRoom->width();
				vStart2 = dataSource->createVertex(pt.x(), pt.y());
				dataSource->add(vStart2);

				pt = *vStartVertical + ptUnitH * officeRoom->width();
				vStartVertical2 = dataSource->createVertex(pt.x(), pt.y());
				dataSource->add(vStartVertical2);
			}

			vOfficeEnd1 = vStart2;
			vOfficeEndV2 = vStartVertical2;
			
			//添加办公室
			officeRoom->addVertex(vStartVertical2);
			if (vStartVertical == vOfficeTarget2)
			{
				MoVertex *vertex = dataSource->createVertex(vStartVertical->x(), vStartVertical->y());
				dataSource->add(vertex);
				officeRoom->addVertex(vertex);
			}
			else		
				officeRoom->addVertex(vStartVertical);
			if (vStart == vOffice)
			{
				MoVertex *vertex = dataSource->createVertex(vStart->x(), vStart->y());
				dataSource->add(vertex);
				officeRoom->addVertex(vertex);
			}
			else
				officeRoom->addVertex(vStart);
			officeRoom->addVertex(vStart2);
			officeRoom->setStartVSeqNo(-1);
			dataSource->add(officeRoom);

			if (bfinish)
			{
				iOffice++;
				break;
			}
		}
		curNum -= iOffice;

		//房间顶点修正
		if (bOrder)
		{
			if (vOfficeEnd1 != vOfficeTarget)
			{
				vOfficeEnd1 = dataSource->createVertex(vOfficeEnd1->x(), vOfficeEnd1->y());
				dataSource->add(vOfficeEnd1);
				void*  vobj = NULL;
				vobj = room->insertAfterVertex(vOffice, vOfficeEnd1);
				MoLine *line = (MoLine*)vobj;
				line->setWallFlag(MoLine::WF_INNER);
			}
			

			if (vOfficeEndV2)
			{
				vOfficeEndV2 = dataSource->createVertex(vOfficeEndV2->x(), vOfficeEndV2->y());
				dataSource->add(vOfficeEndV2);

				void*  vobj = room->insertAfterVertex(vOffice, vOfficeEndV2);
				MoLine *line = (MoLine*)vobj;
				line->setWallFlag(MoLine::WF_INNER);
			}

			if (vOfficeStartV2 != vOfficeTarget2)
			{
				vOfficeStartV2 = dataSource->createVertex(vOfficeStartV2->x(), vOfficeStartV2->y());
				dataSource->add(vOfficeStartV2);

				void*  vobj = room->insertAfterVertex(vOffice, vOfficeStartV2);
				MoLine *line = (MoLine*)vobj;
				line->setWallFlag(MoLine::WF_INNER);
			}
			room->removeVertex(vOffice);
			if (vOfficeEnd1 == vOfficeTarget)
				room->removeVertex(vOfficeEnd1);

			room->setStartVSeqNo(-1);
		}
		else
		{
			if (vOfficeStartV2 != vOfficeTarget2)
			{
				vOfficeStartV2 = dataSource->createVertex(vOfficeStartV2->x(), vOfficeStartV2->y());
				dataSource->add(vOfficeStartV2);

				void*  vobj = room->insertAfterVertex(vOfficeTarget, vOfficeStartV2);
				MoLine *line = (MoLine*)vobj;
				line->setWallFlag(MoLine::WF_INNER);
			}

			if (vOfficeEndV2)
			{
				vOfficeEndV2 = dataSource->createVertex(vOfficeEndV2->x(), vOfficeEndV2->y());
				dataSource->add(vOfficeEndV2);

				void*  vobj = room->insertAfterVertex(vOfficeTarget, vOfficeEndV2);
				MoLine *line = (MoLine*)vobj;
				line->setWallFlag(MoLine::WF_INNER);
			}

			if (vOfficeEnd1 != vOfficeTarget)
			{
				vOfficeEnd1 = dataSource->createVertex(vOfficeEnd1->x(), vOfficeEnd1->y());
				dataSource->add(vOfficeEnd1);
				void*  vobj = NULL;
				vobj = room->insertAfterVertex(vOfficeTarget, vOfficeEnd1);
				MoLine *line = (MoLine*)vobj;
				line->setWallFlag(MoLine::WF_INNER);
			}

			room->removeVertex(vOffice);
			if (vOfficeEnd1 == vOfficeTarget)
				room->removeVertex(vOfficeEnd1);

			room->setStartVSeqNo(-1);
		}

		if (curNum <= 0)break;
	}
	//

	//方案2
	if (type < 1 && dataSourceAnother)
		calOfficeRoom(result, dataSourceAnother, num, 1);
}
