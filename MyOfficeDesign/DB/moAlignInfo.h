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

#ifndef MYOFFICEDESIGN_ALIGNSHAPE_H_
#define MYOFFICEDESIGN_ALIGNSHAPE_H_

#include "moShape.h"
#include "moVertex.h"

namespace MyOffice {
	namespace DB {

		class MO_EXPORT_DLL MoAlignInfo:public MoElement
		{
		public://构造函数
			MoAlignInfo(const nlohmann::json &_json = nullptr);
			virtual MoElementType	getShapeType() { return MET_ALIGNINFO; }

			virtual int				getSeqNo();
			virtual void			setSeqNo(int _id);
			float					getX();
			void					setX(float v);
			float					getY();
			void					setY(float v);
			float					getZ();
			void					setZ(float v);

			
			virtual		nlohmann::json	&toJson();
		};
	}
}
#endif

