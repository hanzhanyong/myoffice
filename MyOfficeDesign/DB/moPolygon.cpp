#include "moPolygon.h"

using namespace MyOffice;
using namespace MyOffice::DB;

MoVertex *MoPolygon::getVertex(unsigned int index)
{
	return m_VertexArray[index];;
}
void	 MoPolygon::addVertex( MoVertex *vertex)
{
	//MoVertex *first = NULL;
	//MoVertex *last = NULL;

	//unsigned int verCount = m_VertexArray.size();
	//if (verCount > 1)
	//{
	//	first = m_VertexArray[0];
	//	last = m_VertexArray[verCount-1];
	//}

	m_VertexArray.push_back(vertex);
}
void	 MoPolygon::addVertex(float x, float y, float z)
{
	MoVertex *vertex = new MoVertex();
	vertex->set(x, y, z);
	addVertex(vertex);
}

