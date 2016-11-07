#include "moDataSource.h"
#include "../3rdParty/nlohmann/json.hpp"

using namespace MyOffice;
using namespace MyOffice::DB;

MoDataSource::~MoDataSource()
{

}
void MoDataSource::setLisener(MoLisener *lisener) 
{ 
	m_Lisener = lisener; 
	int shpCount = m_ShpArray.size();
	for (int i = 0; i < shpCount; i++)
	{
		m_Lisener->updateShape(m_ShpArray[i]);
	}
}
bool MoDataSource::open(const char* fileName)
{
	std::string strSurvey = "";
	FILE *file = NULL;
	file = fopen(fileName, "rb");
	if (file)
	{
		int charNum = 256;
		char *surveyInfo = new char[charNum];

		while (true)
		{
			memset(surveyInfo, 0, charNum);
			size_t iv = fread(surveyInfo, charNum - 1, 1, file);
			strSurvey += surveyInfo;
			if (iv != 1)break;
		}

		fclose(file);
		file = NULL;
	}
	if (strSurvey.length() < 5)return false;
	
	return read(strSurvey.c_str());
}
bool MoDataSource::read(const char* jsonStr) 
{
	
	return true;
}
void MoDataSource::write(const char *data) 
{
	
}
void MoDataSource::add(MoVertex *vertex)
{

}
void MoDataSource::add(MoLine *line)
{
	
}
void MoDataSource::add(MoShape *shp) 
{
	m_ShpArray.push_back(shp);
	if(m_Lisener)m_Lisener->updateShape(shp);
}
void MoDataSource::remove(MoShape *shp)
{
	std::vector<MoShape*>::iterator iter;
	for (iter = m_ShpArray.begin(); iter != m_ShpArray.end();iter++)
	{
		if (*iter == shp)
		{
			if (m_Lisener)m_Lisener->removeShape(shp);
			m_ShpArray.erase(iter);
			delete shp;
			break;
		}
	}
}

