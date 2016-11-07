#include "moRoom.h"
#include "moDataSource.h"
using namespace MyOffice;
using namespace MyOffice::DB;

MoRoom::MoRoom(const nlohmann::json &_json):
	MoPolygon(_json)
{

}
MoRoom::~MoRoom()
{
	MoPolygon::~MoPolygon();
	/*int sizeLine = getLineCount();
	for (int i = 0; i < sizeLine; i++)
	{
		MoLine *line = m_LineArray.at(i);
		delete line;
		m_LineArray.at(i) = NULL;
	}
	m_LineArray.clear();*/
}
int		MoRoom::getStartVSeqNo()
{
	int _seqNo = -1;
	if (m_DataJson["sttVSeqNo"].is_null() == false)
		_seqNo = m_DataJson["sttVSeqNo"].get<int>();
	return _seqNo;
}
void	MoRoom::setStartVSeqNo(int seqNo)
{
	m_DataJson["sttVSeqNo"] = seqNo;
}
void MoRoom::init()
{
	MoDataSource*		dataSource = getDataSource();
	if (dataSource == NULL)return;
	int startSeqNo = getStartVSeqNo();
	MoVertex *vertex = NULL;
	int currentSeqNo = -1;
	while (currentSeqNo != startSeqNo)
	{
		if(currentSeqNo==-1)
			vertex = dataSource->getVertex(startSeqNo);
		else
			vertex = dataSource->getVertex(currentSeqNo);
		currentSeqNo = vertex->getNextSeqNo();

		addVertex(vertex);
	}
}

//void MoRoom::addVertex(MoVertex *vertex)
//{
//	//标记顺时针记录线段的前后关系
//	MoPolygon::addVertex(vertex);
//
//
//	int vertexCount = m_VertexArray.size();
//	if (vertexCount == 0)return;
//
//	MoLine* currentLine = new MoLine();
//	currentLine->setParrent(this);
//	if (vertexCount == 1)
//	{
//		currentLine->start() = *m_VertexArray.at(vertexCount - 1);
//		currentLine->end() = *m_VertexArray.at(vertexCount - 1);
//	}
//	else
//	{
//		currentLine->start() = *m_VertexArray.at(vertexCount - 2);
//		currentLine->end() = *m_VertexArray.at(vertexCount - 1);
//
//		MoLine* firstLine = NULL;
//		MoLine* lastLine = NULL;
//		firstLine = m_LineArray.at(0);
//		lastLine = m_LineArray.at(m_LineArray.size() - 1);
//
//		firstLine->start() = currentLine->end();
//		lastLine->end() = currentLine->start();
//	}
//
//	m_LineArray.push_back(currentLine);
//}
		

nlohmann::json	&MoRoom::toJson()
{
	if (m_DataJson["type"].is_null())m_DataJson["type"] = "room";
	return MoPolygon::toJson();
}