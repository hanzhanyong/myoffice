// testWin32.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <DB/moDataSource.h>
#include <Analyse/moAnalyse.h>

void testWrite()
{
	MyOffice::DB::MoDataSource *datasource = new MyOffice::DB::MoDataSource();
	datasource->open("D:\\jsonDemo1.json");

	MyOffice::DB::MoRoom *roomSource = datasource->getRoom(0);

	MyOffice::DB::MoRoom *room = dynamic_cast<MyOffice::DB::MoRoom *>(roomSource->cloneStruct());

	MyOffice::DB::MoVertex *vertex = datasource->createVertex(5000, 200);
	datasource->add(vertex);
	room->setStartVSeqNo(vertex->getSeqNo());

	room->addVertex(vertex);

	vertex = datasource->createVertex(-5000, 200);
	datasource->add(vertex);
	room->addVertex(vertex);

	vertex = datasource->createVertex(-5000, 7000);
	datasource->add(vertex);
	room->addVertex(vertex);

	vertex = datasource->createVertex(5000, 7000);
	datasource->add(vertex);
	room->addVertex(vertex);

	datasource->add(room);

	datasource->save("D:\\jsonDemoResult.json");

	delete datasource;
}
void testAnalyse()
{
	MyOffice::DB::MoDataSource *datasource = new MyOffice::DB::MoDataSource();
	datasource->open("D:\\jsonDemo4.json");

	MyOffice::DB::MoRoom *roomSource = datasource->getRoomIndex(0);
	MyOffice::DB::MoDoor *doorSource = datasource->getDoorOnRoom(roomSource);

	MyOffice::Analyse::MoAnalyse *analyse = new MyOffice::Analyse::MoAnalyse();
	analyse->autoCal(roomSource, doorSource);
	datasource->save("D:\\jsonDemoResult.json");

	delete datasource;
}
int main()
{
	//testWrite();
	
	testAnalyse();
    return 0;
}


