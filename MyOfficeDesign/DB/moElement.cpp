
#include "moElement.h"

using namespace MyOffice;
using namespace MyOffice::DB;

MoElement::MoElement(const nlohmann::json &_json):
	m_DataJson(_json)
{
	if (m_DataJson == nullptr)
		m_DataJson["seqNo"] = -1;
}
int	 MoElement::getSeqNo() 
{ 
	int _seqNo = -1;
	if (!m_DataJson["seqNo"].is_null())
		_seqNo = m_DataJson["seqNo"].get<int>();
	return _seqNo;
}
void MoElement::setSeqNo(int _id) 
{ 
	m_DataJson["seqNo"] = _id;
}
nlohmann::json	&MoElement::toJson()
{
	return m_DataJson;
}