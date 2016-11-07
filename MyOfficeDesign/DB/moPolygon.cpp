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
void MoPolygon::insertVertex(MoVertex *vertex, unsigned int index)
{
	m_VertexArray.insert(m_VertexArray.begin() + index, vertex);
}
nlohmann::json	&MoPolygon::toJson()
{
	int numVertex = getVertexCount();
	for (int i = 0; i < numVertex; i++)
	{
		MoVertex *vertex0 = i == 0 ? m_VertexArray[numVertex - 1] : m_VertexArray[i - 1];
		MoVertex *vertex1 = m_VertexArray[i];
		MoVertex *vertex2 = i == numVertex - 1 ? m_VertexArray[0] : m_VertexArray[i + 1];

		vertex1->setNextSeqNo(vertex2->getSeqNo());
		vertex1->setPreSeqNo(vertex0->getSeqNo());
	}


	return MoElement::toJson();
}