// testWin32.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <DB/moDataSource.h>
#include <Analyse/moAnalyse.h>
int main()
{
	MyOffice::DB::MoDataSource *datasource = new MyOffice::DB::MoDataSource();
	datasource->open("D:\\jsonDemo1.json");

	MyOffice::DB::MoRoom *roomSource = datasource->getRoom(0);

	MyOffice::DB::MoRoom *room = dynamic_cast<MyOffice::DB::MoRoom *>( roomSource->clone());
	
	MyOffice::DB::MoVertex *vertex = datasource->createVertex(5000, 200);
	room->addVertex(vertex);
	vertex = datasource->createVertex(-5000, 200);
	room->addVertex(vertex);
	vertex = datasource->createVertex(-5000, 7000);
	room->addVertex(vertex);
	vertex = datasource->createVertex(5000, 7000);
	room->addVertex(vertex);
	datasource->add(room);

	datasource->save("D:\\jsonDemoResult.json");



	///MyOffice::Analyse::MoAnalyse *analyse = new MyOffice::Analyse::MoAnalyse();



	/*MyOffice::DB::MoRoom room;*/
	//room.addVertex();

    return 0;
}

