#include "moAlignInfo.h"

using namespace MyOffice;
using namespace MyOffice::DB;
MoAlignInfo::MoAlignInfo(const nlohmann::json &_json):
	MoElement(_json)
{

}
float					MoAlignInfo::getX()
{
	float _value = 0.0;
	if (!m_DataJson["x"].is_null())
		_value = m_DataJson["x"].get<float>();
	return _value;
}
void					MoAlignInfo::setX(float v)
{
	m_DataJson["x"] = v;
}
float					MoAlignInfo::getY()
{
	float _value = 0.0;
	if (!m_DataJson["y"].is_null())
		_value = m_DataJson["y"].get<float>();
	return _value;
}
void					MoAlignInfo::setY(float v)
{
	m_DataJson["y"] = v;
}
float					MoAlignInfo::getZ()
{
	float _value = 0.0;
	if (!m_DataJson["z"].is_null())
		_value = m_DataJson["z"].get<float>();
	return _value;
}
void					MoAlignInfo::setZ(float v)
{
	m_DataJson["z"] = v;
}
nlohmann::json	&MoAlignInfo::toJson()
{
	//m_DataJson["x"] = getX()+1;
	//m_DataJson["y"] = getY()+1;
	//m_DataJson["z"] = getZ()+1;

	return MoElement::toJson();
}

