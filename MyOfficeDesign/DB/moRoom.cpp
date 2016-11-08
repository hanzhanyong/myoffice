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
	int sizeLine = getLineCount();
	for (int i = 0; i < sizeLine; i++)
	{
		MoLine *line = m_LineArray.at(i);
		delete line;
		m_LineArray.at(i) = NULL;
	}
	m_LineArray.clear();
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
		currentSeqNo = vertex->getPreSeqNo();

		addVertex(vertex);
	}
}

void MoRoom::addVertex(MoVertex *vertex)
{
	//标记顺时针记录线段的前后关系
	MoPolygon::addVertex(vertex);


	int vertexCount = m_VertexArray.size();

	MoLine* currentLine = new MoLine();
	currentLine->setParrent(this);
	if (vertexCount == 1)
	{
		currentLine->setStart(m_VertexArray.at(vertexCount - 1));
		currentLine->setEnd(m_VertexArray.at(vertexCount - 1));
	}
	else
	{
		currentLine->setStart(m_VertexArray.at(vertexCount - 2));
		currentLine->setEnd(m_VertexArray.at(vertexCount - 1));

		MoLine* firstLine = NULL;
		MoLine* lastLine = NULL;
		firstLine = m_LineArray.at(0);
		lastLine = m_LineArray.at(m_LineArray.size() - 1);

		firstLine->setStart(currentLine->end());
		lastLine->setEnd(currentLine->start());
	}

	m_LineArray.push_back(currentLine);
}
void	MoRoom::removeVertex(MoVertex *vertex)
{
	std::vector<MoLine*>::iterator itor = m_LineArray.begin();
	while (itor != m_LineArray.end())
	{
		MoLine* currentLine = *itor;
		if (currentLine->start() == vertex)
		{
			int seqNo = vertex->getNextSeqNo();
			MoLine *afterLineNext = getLine(seqNo);

			afterLineNext->setEnd(currentLine->end());

			delete currentLine;
			m_LineArray.erase(itor);
			break;
		}

		itor++;
	}
	MoPolygon::removeVertex(vertex);
}
void*	MoRoom::insertAfterVertex(MoVertex* after, MoVertex *vertexNew)
{
	MoPolygon::insertAfterVertex(after, vertexNew);

	std::vector<MoLine*>::iterator itor = m_LineArray.begin();
	while (itor != m_LineArray.end())
	{
		MoLine *afterLine = *itor;
		if (afterLine->start() == after)
		{
			MoLine *afterLinePre = getLine(after->getPreSeqNo());
			MoLine* currentLine = new MoLine();
			currentLine->setParrent(this);
			itor++;
			m_LineArray.insert(itor, currentLine);

			currentLine->setStart(vertexNew);
			currentLine->setEnd(afterLinePre->start());

			afterLine->setEnd(vertexNew);
			return currentLine;
		}
		itor++;
	}
	
	return NULL;
}
MoLine	*MoRoom::getLine(int vStartSeqNo)
{
	int sizeLine = getLineCount();
	for (int i = 0; i < sizeLine; i++)
	{
		MoLine *line = m_LineArray[i];

		int seqNo = line->start()->getSeqNo();
		if (seqNo == vStartSeqNo)
			return line;
	}
	return NULL;
}

nlohmann::json	&MoRoom::toJson()
{
	if (m_DataJson["type"].is_null())m_DataJson["type"] = "room";
	return MoPolygon::toJson();
}