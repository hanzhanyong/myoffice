﻿// testWin32.cpp : 定义控制台应用程序的入口点。
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
	datasource->open("D:\\mapftest\\jsonDemo16.json");

	MyOffice::Analyse::MoAnalyseResult *result = 
		MyOffice::Analyse::MoAnalyse::autoAnalyse(datasource);
	

	char fileName[128];
	unsigned int analyseCount = result->getDataSourceCount();
	for (unsigned int i = 0; i < analyseCount; i++)
	{
		MyOffice::DB::MoDataSource *ds = result->getDataSource(i);
		
		sprintf_s(fileName, "D:\\mapftest\\jsonDemoResult%d.json", i);
		ds->save(fileName);
	}
	

	delete result;
}
int main()
{
	//testWrite();
	
	testAnalyse();
    return 0;
}


