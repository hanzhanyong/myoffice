#include "moRoomRect.h"

using namespace MyOffice;
using namespace MyOffice::DB;


MoRoomRect::MoRoomRect(const nlohmann::json &_json):
	m_Length(4500),
	m_Width(3500),
	m_RoomType(RT_MEDIUM),
	MoRoom(_json)
{
	/*房间的规格 (单位米)
	1、办公室
	    大     5.0 X 4.0
		中     4.5 X 3.5
		小     4.0 X 3.0
	2、会议室
		大     5.0 X 4.0
		中     4.5 X 3.5
		小     4.0 X 3.0
	3、前台
		大     5.0 X 4.0
		中     4.5 X 3.5
		小     4.0 X 3.0
	
		小小   3.0 X 2.0
	工位的规格
	
	*/
}
void			MoRoomRect::setRoomType(RoomType type)
{
	m_RoomType = type;
	switch (type)
	{
	case MyOffice::DB::MoRoomRect::RT_LARGE:
		m_Length = 5000;
		m_Width = 4000;
		break;
	case MyOffice::DB::MoRoomRect::RT_MEDIUM:
		m_Length = 4500;
		m_Width = 3500;
		break;
	case MyOffice::DB::MoRoomRect::RT_SMALL:
		m_Length = 4000;
		m_Width = 3000;
		break;
	case MyOffice::DB::MoRoomRect::RT_SMALLSMALL:
		m_Length = 3000;
		m_Width = 2000;
		break;
	default:
		m_Length = 5000;
		m_Width = 4000;
		break;
	}
}