#include "moDoor.h"
#include "moDataSource.h"

using namespace MyOffice;
using namespace MyOffice::DB;

MoDoor::MoDoor(const nlohmann::json &_json) :
	m_AlignInfo1(NULL),
	m_AlignInfo2(NULL),
	MoShape(_json)
{
	if (!m_DataJson["alignInfo1"].is_null())
		m_AlignInfo1 = new MoAlignInfo(m_DataJson["alignInfo1"]);
	if (!m_DataJson["alignInfo2"].is_null())
		m_AlignInfo2 = new MoAlignInfo(m_DataJson["alignInfo2"]);
}
MoDoor::~MoDoor()
{
	if (m_AlignInfo1)
		delete m_AlignInfo1;
	m_AlignInfo1 = NULL;

	if (m_AlignInfo2)
		delete m_AlignInfo2;
	m_AlignInfo2 = NULL;
}
MoElement *	   MoDoor::clone()
{
	nlohmann::json &data = this->toJson();
	MoDoor *shp = new MoDoor(data);
	return shp;
}
float		MoDoor::getWidth()
{
	float _width = 900;
	if (!m_DataJson["width"].is_null())
		_width = m_DataJson["width"].get<int>();
	return _width;
}
void		MoDoor::setWidth(float w)
{
	m_DataJson["width"] = w;
}

float		MoDoor::getHeight()
{
	float _value = 2700;
	if (!m_DataJson["height"].is_null())
		_value = m_DataJson["height"].get<int>();
	return _value;
}
void		MoDoor::setHeight(float h)
{
	m_DataJson["height"] = h;
}

float		MoDoor::getThickness()
{
	float _value = 240;
	if (!m_DataJson["thickness"].is_null())
		_value = m_DataJson["thickness"].get<int>();
	return _value;
}
void		MoDoor::setThickness(float t)
{
	m_DataJson["thickness"] = t;
}
MoVertex			   *MoDoor::alignInfo1Vertex()
{
	if (alignInfo1())
	{
		MoDataSource *dataSource = this->getDataSource();
		return dataSource->getVertex(alignInfo1()->getSeqNo());
	}
	return NULL;
}
MoVertex			   *MoDoor::alignInfo2Vertex()
{
	if (alignInfo2())
	{
		MoDataSource *dataSource = this->getDataSource();
		return dataSource->getVertex(alignInfo2()->getSeqNo());
	}
	return NULL;
}
Vec3f		MoDoor::getLocation()
{
	MoDataSource *dataSource = this->getDataSource();
	MoVertex *vertex = alignInfo1Vertex();
	if (vertex == NULL)
		vertex = alignInfo2Vertex();
	MoVertex *vertexNext = dataSource->getVertex(vertex->getNextSeqNo());

	Vec3f loc = *vertexNext - *vertex;
	loc.normalize();
	loc = (*vertex) + loc*(this->getWidth() / 2.0+ alignInfo1()->getX());
	return loc;
}
nlohmann::json	&MoDoor::toJson()
{
	if (m_AlignInfo1)
		m_DataJson["alignInfo1"] = m_AlignInfo1->toJson();

	if (m_AlignInfo2)
		m_DataJson["alignInfo2"] = m_AlignInfo2->toJson();

	if (m_DataJson["type"].is_null())m_DataJson["type"] = "shape-door";

	return MoElement::toJson();
}