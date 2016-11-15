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

#ifndef MYOFFICEDESIGN_ANALYSERESULT_H_
#define MYOFFICEDESIGN_ANALYSERESULT_H_

#include "../Common/moExport.h"
#include <vector>

namespace MyOffice {
	namespace DB {
		class MoDataSource;
	}
	namespace Analyse {

		class MO_EXPORT_DLL MoAnalyseResult
		{
		public:
			MoAnalyseResult();
			~MoAnalyseResult();

			//可在分解的数据源
			DB::MoDataSource *getValidAnalyzeDS(int roomType);

			unsigned int      getDataSourceCount();
			DB::MoDataSource *getDataSource(unsigned int index);
			//DB::MoDataSource *getFirstDataSource();
			//DB::MoDataSource *getNextDataSource();
			void addDataSource(DB::MoDataSource *dataSource);

		private:
			void			  release();
			bool			  exists(DB::MoDataSource *ds);

			std::vector<DB::MoDataSource *>	m_DataSourceArray;
		};
	}
}
#endif

