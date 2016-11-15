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

//2 办公室区域计算
void MoAnalyse::calOfficeRoom(MoAnalyseResult *result, int num)
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
void MoAnalyse::calOfficeRoom(MoDataSource *result, int num)
{

}
