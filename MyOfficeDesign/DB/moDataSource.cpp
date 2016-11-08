#include "moDataSource.h"
#include "../3rdParty/nlohmann/json.hpp"

using namespace MyOffice;
using namespace MyOffice::DB;

using namespace nlohmann;



MoDataSource::~MoDataSource()
{

}
void MoDataSource::setLisener(MoLisener *lisener) 
{ 
	m_Lisener = lisener; 
	/*int shpCount = m_ShpArray.size();
	for (int i = 0; i < shpCount; i++)
	{
		m_Lisener->updateShape(m_ShpArray[i]);
	}*/
}
bool MoDataSource::open(const char* fileName)
{
	std::string strSurvey = "";
	FILE *file = NULL;
	file = fopen(fileName, "rb");
	if (file)
	{
		int charNum = 256;
		char *surveyInfo = new char[charNum];

		while (true)
		{
			memset(surveyInfo, 0, charNum);
			size_t iv = fread(surveyInfo, charNum - 1, 1, file);
			strSurvey += surveyInfo;
			if (iv != 1)break;
		}

		fclose(file);
		file = NULL;
	}
	if (strSurvey.length() < 5)return false;
	
	return readJson(strSurvey.c_str());
}
bool MoDataSource::save(const char* fileName)
{
	FILE *file = NULL;
	file = fopen(fileName, "wb");
	if (file)
	{
		std::string dataStr = getJson();
		fwrite(dataStr.c_str(), 1, dataStr.length(), file);
		fclose(file);
	}
	return true;
}
bool MoDataSource::readJson(const char* src) 
{
	json obj;
	std::string dataStr;

	bool compress = false;
	if (compress)
	{
		//std::string decodeStr = gloox::Base64::decode64(src);
		////解压缩 
		//unsigned long  achcompLen = decodeStr.length();
		//unsigned char *achcomp = (unsigned char*)decodeStr.c_str();

		//unsigned long  dataLen = achcompLen * 10;
		//unsigned char *data = (unsigned char *)malloc(dataLen);
		//memset(data, 0, dataLen);

		//uncompress((unsigned char*)data, &dataLen, achcomp, achcompLen);
		//dataStr = (char *)data;
	}
	else
	{
		dataStr = src;
	}
	obj = json::parse(dataStr);

	m_Version = obj["version"].get<std::string>();
	m_IsCorrected = obj["isCorrected"].get<bool>();
	m_CurrentRoomSeqNo = obj["roomSeqNo"].get<int>();
	m_CurrentShapeSeqNo = obj["shapeSeqNo"].get<int>();
	m_CurrentVertexSeqNo = obj["vertexSeqNo"].get<int>();
	
	json j = obj["vertices"];
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		json temp = *it;
		MoVertex* vertex = new MoVertex(temp);
		this->add(vertex);
	}
	j = obj["rooms"];
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		json temp = *it;
		MoRoom* room = new MoRoom(temp);
		room->setDataSource(this);
		room->init();
		this->add(room);
	}
	j = obj["shapes"];
	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		json temp = *it;
		if (temp["type"].is_null() == false && temp["type"] == "shape-door")
		{
			MoDoor *door = new MoDoor(temp);
			door->setDataSource(this);
			door->init();
			this->add(door);
		}
	}
	return true;
}
std::string MoDataSource::getJson()
{
	json obj;
	obj["version"] = m_Version;
	obj["isCorrected"] = m_IsCorrected;
	obj["roomSeqNo"] = m_CurrentRoomSeqNo;
	obj["shapeSeqNo"] = m_CurrentShapeSeqNo;
	obj["vertexSeqNo"] = m_CurrentVertexSeqNo;


	json vertd = json::array();
	json roomd = json::array();
	json shaped = json::array();

	std::vector<MoElement*>::iterator itor;

	itor = m_RoomArray.begin();
	while (itor != m_RoomArray.end()) {
		json data = (*itor)->toJson();
		roomd.push_back(data);
		itor++;
	}

	itor = m_DoorArray.begin();
	while (itor != m_DoorArray.end()) {
		json data = (*itor)->toJson();
		shaped.push_back(data);
		itor++;
	}

	itor = m_VertexArray.begin();
	while (itor != m_VertexArray.end()) {
		json data = (*itor)->toJson();
		vertd.push_back(data);
		itor++;
	}

	obj["vertices"] = vertd;
	obj["rooms"] = roomd;
	obj["shapes"] = shaped;

	std::string updataStr = obj.dump();
	/*if (isCompress)
	{
		char *  m_HouseInfo;
		int m_HouseInfoCount;
		int bLen = updataStr.length();
		if (m_HouseInfoCount < bLen)
		{
			m_HouseInfoCount = bLen;
			if (m_HouseInfo)free(m_HouseInfo);
			m_HouseInfo = (char *)malloc(m_HouseInfoCount);
		}
		memset(m_HouseInfo, 0, m_HouseInfoCount);
		unsigned long nCompLen = m_HouseInfoCount;
		compress((Bytef *)m_HouseInfo, &nCompLen, (Bytef *)updataStr.c_str(), bLen);

		char *outBase64 = (char*)malloc(nCompLen * 2);
		memset(outBase64, 0, nCompLen * 2);
		gloox::Base64::encode64(m_HouseInfo, nCompLen, outBase64);

		memset(m_HouseInfo, 0, m_HouseInfoCount);
		memcpy(m_HouseInfo, outBase64, strlen(outBase64));
		free(outBase64);
		updataStr = m_HouseInfo;
		if (m_HouseInfo)free(m_HouseInfo);
	}*/
	return updataStr;
}
//void MoDataSource::add(float x, float y)
//{
//	MoVertex *vertex = new MoVertex();
//	vertex->set(x, y);
//	vertex->setSeqNo(m_CurrentVertexSeqNo);
//	m_CurrentVertexSeqNo++;
//	add(vertex);
//}
MoVertex *   MoDataSource::getVertex(int seqNo)
{
	int sizeV = m_VertexArray.size();
	for (int i = 0; i < sizeV; i++)
	{
		MoElement *ele = m_VertexArray[i];
		if (ele->getSeqNo() == seqNo)
			return dynamic_cast<MoVertex*>(ele);
	}
	return NULL;
}
MoVertex *   MoDataSource::createVertex(float x, float y)
{
	MoVertex *vertex = new MoVertex();
	vertex->setSeqNo(m_CurrentVertexSeqNo++);
	vertex->set(x, y);
	return vertex;
}
unsigned int MoDataSource::getRoomCount()
{
	return m_RoomArray.size();
}
MoRoom		*MoDataSource::getRoomIndex(unsigned int index)
{
	MoElement *ele = m_RoomArray[index];
	return dynamic_cast<MoRoom*>(ele);
}
MoDoor		*MoDataSource::getDoorOnRoom(MoRoom		*room)
{
	unsigned int vertexCount = room->getVertexCount();
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		MoVertex *vertexRoom = room->getVertex(i);
		unsigned int doorCount = m_DoorArray.size();
		for (unsigned int j = 0; j < doorCount; j++)
		{
			MoDoor *door = dynamic_cast<MoDoor*>( m_DoorArray[j]);
			MoAlignInfo *alignInfo = door->alignInfo1();
			if (alignInfo&&alignInfo->getSeqNo()==vertexRoom->getSeqNo())
			{
				return door;
			}
			alignInfo = door->alignInfo2();
			if (alignInfo&&alignInfo->getSeqNo() == vertexRoom->getSeqNo())
			{
				return door;
			}
		}
	}
	return NULL;
}
MoRoom	*MoDataSource::getRoom(int seqNo)
{
	int sizeV = m_RoomArray.size();
	for (int i = 0; i < sizeV; i++)
	{
		MoElement *ele = m_RoomArray[i];
		if (ele->getSeqNo() == seqNo)
			return dynamic_cast<MoRoom*>(ele);
	}
	return NULL;
}

MoRoom	*MoDataSource::getRoomVertex(int vseqNo)
{
	unsigned int sizeV = m_RoomArray.size();
	for (unsigned int i = 0; i < sizeV; i++)
	{
		MoRoom *room = dynamic_cast<MoRoom*>(m_RoomArray[i]);
		int vertexCount = room->getVertexCount();
		for (unsigned int j = 0; j < vertexCount; j++)
		{
			MoVertex *vertex = room->getVertex(j);
			if (vertex->getSeqNo() == vseqNo)
			{
				return room;
			}
		}
	}
	return NULL;
}
MoDoor  *MoDataSource::getDoor(int seqNo)
{
	int sizeV = m_DoorArray.size();
	for (int i = 0; i < sizeV; i++)
	{
		MoElement *ele = m_DoorArray[i];
		if (ele->getSeqNo() == seqNo)
			return dynamic_cast<MoDoor*>(ele);
	}
	return NULL;
}
void MoDataSource::add(MoVertex *vertex)
{
	if (vertex->getSeqNo() < 0)
	{
		vertex->setSeqNo(m_CurrentVertexSeqNo);
		m_CurrentVertexSeqNo++;
	}
	m_VertexArray.push_back(vertex);
}
void MoDataSource::add(MoRoom *room)
{
	if (room->getSeqNo() < 0)
	{
		room->setSeqNo(m_CurrentRoomSeqNo);
		m_CurrentRoomSeqNo++;
	}
	m_RoomArray.push_back(room);
}
void MoDataSource::add(MoDoor *door)
{
	if (door->getSeqNo() < 0)
	{
		door->setSeqNo(m_CurrentShapeSeqNo);
		m_CurrentShapeSeqNo++;
	}
	m_DoorArray.push_back(door);
}
//void MoDataSource::add(MoShape *shp) 
//{
//	m_ShpArray.push_back(shp);
//	if(m_Lisener)m_Lisener->updateShape(shp);
//}
//void MoDataSource::remove(MoShape *shp)
//{
//	std::vector<MoShape*>::iterator iter;
//	for (iter = m_ShpArray.begin(); iter != m_ShpArray.end();iter++)
//	{
//		if (*iter == shp)
//		{
//			if (m_Lisener)m_Lisener->removeShape(shp);
//			m_ShpArray.erase(iter);
//			delete shp;
//			break;
//		}
//	}
//}

