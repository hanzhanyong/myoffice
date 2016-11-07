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
#include "../Common/moVec.h"
#include "../DB/moPolygon.h"
#include "../DB/moRectRoom.h"
#include "../DB/moRoom.h"
#include "../DB/moDataSource.h"

namespace MyOffice {
	namespace Analyse {

		class MO_EXPORT_DLL MoAnalyse
		{
		public:
			//默认1前台  1会议室  2办公室
			DB::MoDataSource *autoCal(const DB::MoRoom* room, int roomQTCount = 1, int roomHYCount = 1, int roomOfficeCount = 2 );

		private:
			//办公室内提取未被占领区域
			virtual DB::MoRoom	*cutRoom(const DB::MoRoom* source,const DB::MoRectRoom* cutRect) { return NULL; };
		};
	}
}
#endif

