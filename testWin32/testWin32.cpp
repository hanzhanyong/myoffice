// testWin32.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <DB/moDataSource.h>
#include <Analyse/moAnalyse.h>
int main()
{
	MyOffice::DB::MoDataSource *datasource = new MyOffice::DB::MoDataSource();
	datasource->read("");

	MyOffice::Analyse::MoAnalyse *analyse = new MyOffice::Analyse::MoAnalyse();



	/*MyOffice::DB::MoRoom room;*/
	//room.addVertex();

    return 0;
}

