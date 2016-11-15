#include "moAnalyse.h"
#include "moAnalyseResult.h"

#include "../Common/moVec.h"
#include "../Common/moMath.h"
#include "../Common/moMatrix.h"

#include "../DB/moDoor.h"
#include "../DB/moRoom.h"
#include "../DB/moRoomRect.h"
#include "../DB/moDataSource.h"

using namespace MyOffice;
using namespace MyOffice::DB;
using namespace MyOffice::Analyse;


//3 前台、办公室的门口位置
void MoAnalyse::calDoorOfRoom(MoAnalyseResult *result)
{
	/*if (num == 0)return;
	if (result->getDataSourceCount() == 0)return;

	MoDataSource *ds = result->getValidAnalyzeDS();
	while (ds)
	{
		calOfficeRoom(ds, num);
		ds = result->getValidAnalyzeDS();
	}*/
}
void MoAnalyse::calDoorOfRoom(MoDataSource *ds)
{

}