
#include "moVertex.h"

using namespace MyOffice;
using namespace MyOffice::DB;

MoVertex::MoVertex(const nlohmann::json &_json):
MoElement(_json)
{
	if (!m_DataJson["x"].is_null())x() = m_DataJson["x"].get<float>();
	if (!m_DataJson["y"].is_null())y() = m_DataJson["y"].get<float>();
}
int			MoVertex::getNextSeqNo()
{
	int _seqNo = -1;
	if (m_DataJson["nVSeqNo"].is_null() == false)
		_seqNo = m_DataJson["nVSeqNo"].get<int>();
	return _seqNo;
}
void		MoVertex::setNextSeqNo(int seqNo)
{
	m_DataJson["nVSeqNo"] = seqNo;
}
int			MoVertex::getPreSeqNo()
{
	int _seqNo = -1;
	if (m_DataJson["pVSeqNo"].is_null() == false)
		_seqNo = m_DataJson["pVSeqNo"].get<int>();
	return _seqNo;
}
void		MoVertex::setPreSeqNo(int seqNo)
{
	m_DataJson["pVSeqNo"] = seqNo;
}
nlohmann::json	&MoVertex::toJson()
{
	m_DataJson["x"] = x();
	m_DataJson["y"] = y();
	if (m_DataJson["type"].is_null())m_DataJson["type"] = "vertex";
	return MoElement::toJson();
}