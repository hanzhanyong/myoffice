/************ C++ ********  MyOfficeDesign Engine (MIT License)   ***********************
************************** Copyright (C) 2014-2016 mapf.cn ***********************
**************************     author:hanzhanyong          ***********************
**************************     email:306679711@qq.com      ***********************
**************************     http://www.mapf.cn          ***********************

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************************/

#ifndef MYOFFICEDESIGN_ANALYSE_H_
#define MYOFFICEDESIGN_ANALYSE_H_

#include "../Common/moExport.h"
#include "moAnalyseResult.h"

namespace MyOffice {
	namespace DB {
		class MoDataSource;
	}
	namespace Analyse {
		class MO_EXPORT_DLL MoAnalyse
		{
		public:
			
			static MoAnalyseResult *autoAnalyse(
				DB::MoDataSource *dataSource, 
				int roomQTCount = 1,		 //默认1前台，取值范围(0,1)
				int roomHYCount = 1,		 //默认1会议室，取值范围(0,3)
				int roomOfficeCount = 2 );   //默认2办公室，取值范围(0,5)

		private:

			//1 前台区域计算
			static void calReceptionRoom(MoAnalyseResult *result, int num);
			static void calReceptionRoom(DB::MoDataSource *ds, int num);
			//2 办公室区域计算
			static void calOfficeRoom(MoAnalyseResult *result, int num);
			static void calOfficeRoom(MoAnalyseResult *result, DB::MoDataSource *ds, int num,int type=0);
			//3 前台、办公室的门口位置
			static void calDoorOfRoom(MoAnalyseResult *result);
			static void calDoorOfRoom(DB::MoDataSource *ds);
			//4 主通道的道路计算
			static void calMailRoad(MoAnalyseResult *result);
			static void calMailRoad(DB::MoDataSource *ds);
			//5 使用主道路切割多个剩余区域
			static void calCutZone(MoAnalyseResult *result);
			static void calCutZone(DB::MoDataSource *ds);
			//6 在剩余区域内，会议室区域计算
			static void calMeetingRoom(MoAnalyseResult *result);
			static void calMeetingRoom(DB::MoDataSource *ds);
			//7 房间、房门数据修正适应家美美数据格式
			static void adjustData(MoAnalyseResult *result);
			static void adjustData(DB::MoDataSource *ds);

			//8 各个房间虚拟矩形
			//9 家具摆放
		};
	}
}
#endif

