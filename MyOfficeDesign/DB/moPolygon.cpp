#include "moPolygon.h"

using namespace MyOffice;
using namespace MyOffice::DB;

MoVertex *MoPolygon::getVertex(unsigned int index)
{
	return m_VertexArray[index];;
}

//void	 MoPolygon::addVertex(float x, float y, float z)
//{
//	MoVertex *vertex = new MoVertex();
//	vertex->set(x, y, z);
//	addVertex(vertex);
//}
void	 MoPolygon::addVertex( MoVertex *vertex)
{
	m_VertexArray.push_back(vertex);
}
void	MoPolygon::removeVertex(MoVertex *vertex)
{
	std::vector<MoVertex*>::iterator itor = m_VertexArray.begin();
	while (itor != m_VertexArray.end())
	{
		if ((*itor) == vertex)
		{
			m_VertexArray.erase(itor);
			return;
		}
		itor++;
	}
}
void* MoPolygon::insertAfterVertex(MoVertex* after, MoVertex *vertex)
{
	std::vector<MoVertex*>::iterator itor = m_VertexArray.begin();
	while (itor != m_VertexArray.end())
	{
		if ((*itor) == after)
		{
			itor++;
			m_VertexArray.insert(itor,vertex);
			return NULL;
		}
		itor++;
	}
	return NULL;
}

nlohmann::json	&MoPolygon::toJson()
{
	int numVertex = getVertexCount();
	for (int i = 0; i < numVertex; i++)
	{
		MoVertex *vertex0 = i == 0 ? m_VertexArray[numVertex - 1] : m_VertexArray[i - 1];
		MoVertex *vertex1 = m_VertexArray[i];
		MoVertex *vertex2 = i == numVertex - 1 ? m_VertexArray[0] : m_VertexArray[i + 1];

		vertex1->setNextSeqNo(vertex0->getSeqNo());
		vertex1->setPreSeqNo(vertex2->getSeqNo());
	}


	return MoElement::toJson();
}