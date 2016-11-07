
#include "moShape.h"
#include "moRoom.h"
#include "moDoor.h"

using namespace MyOffice;
using namespace MyOffice::DB;

MoShape::MoShape(const nlohmann::json &_json) :
	m_Name("Shape"),
	m_DataSource(NULL),
	MoElement(_json)
{
}
const std::string&			MoShape::getName()
{
	if (!m_DataJson["name"].is_null())
		m_Name =  m_DataJson["name"].get<std::string>();
	return m_Name;
}
void					MoShape::setName(const std::string& name)
{
	m_Name = name;
	m_DataJson["name"] = name;
}
MoShape	   *MoShape::clone()
{
	MoShape *shp = NULL;

	if (m_DataJson["type"].is_null() == false)
	{
		if (m_DataJson["type"].get<std::string>() == "room")
		{
			shp = new MoRoom(m_DataJson);
		}
		else if (m_DataJson["type"].get<std::string>() == "shape-door")
		{
			shp = new MoDoor(m_DataJson);
		}
	}
	if (shp)
		shp->setSeqNo(-1);
	return shp;
}