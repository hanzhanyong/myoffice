#include "moAnalyseResult.h"
#include "../DB/moDataSource.h"

using namespace MyOffice;
using namespace MyOffice::DB;
using namespace MyOffice::Analyse;



MoAnalyseResult::MoAnalyseResult()
{}
MoAnalyseResult::~MoAnalyseResult()
{
	this->release();
}

void MoAnalyseResult::release()
{
	std::vector<MoDataSource*>::iterator itor = m_DataSourceArray.begin();
	while (itor != m_DataSourceArray.end())
	{
		MoDataSource *_ds = *itor;
		delete _ds;

		itor++;
	}
	m_DataSourceArray.clear();
}

DB::MoDataSource *MoAnalyseResult::getValidAnalyzeDS(int roomType)
{
	std::vector<MoDataSource*>::iterator itor = m_DataSourceArray.begin();
	while (itor != m_DataSourceArray.end())
	{
		MoDataSource *_ds = *itor;

		bool validDS = true;
		unsigned int roomCount = _ds->getRoomCount();
		for (unsigned int i = 0; i < roomCount; i++)
		{
			MoRoom *room = _ds->getRoomIndex(i);
			if (room->getRoomType() == roomType)
			{
				validDS = false;
				break;
			}
		}
		if (validDS)return _ds;
		itor++;
	}
	return NULL;
}

unsigned int      MoAnalyseResult::getDataSourceCount()
{
	return 	m_DataSourceArray.size();
}
DB::MoDataSource *MoAnalyseResult::getDataSource(unsigned int index)
{
	return m_DataSourceArray[index];
}
//DB::MoDataSource *MoAnalyseResult::getFirstDataSource()
//{
//
//}
//DB::MoDataSource *MoAnalyseResult::getNextDataSource()
//{
//
//}
void MoAnalyseResult::addDataSource(DB::MoDataSource *dataSource)
{
	if (exists(dataSource))return;

	m_DataSourceArray.push_back(dataSource);
}
bool  MoAnalyseResult::exists(DB::MoDataSource *ds)
{
	std::vector<MoDataSource*>::iterator itor = m_DataSourceArray.begin();
	while (itor != m_DataSourceArray.end())
	{
		MoDataSource *_ds = *itor;
		if (_ds == ds)
			return true;
		itor++;
	}
	return false;
}