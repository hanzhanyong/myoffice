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

#ifndef MYOFFICEDESIGN_ARRAY_H_
#define MYOFFICEDESIGN_ARRAY_H_

#include "moExport.h"
#include "moGL.h"
#include "moVec.h"
#include "moMatrix.h"


namespace MyOffice {

	class Arraylist
	{
	public:
		enum Type
		{
			ArrayType = 0,

			ByteArrayType = 1,
			ShortArrayType = 2,
			IntArrayType = 3,

			UByteArrayType = 4,
			UShortArrayType = 5,
			UIntArrayType = 6,

			FloatArrayType = 7,
			DoubleArrayType = 8,

			Vec2bArrayType = 9,
			Vec3bArrayType = 10,
			Vec4bArrayType = 11,

			Vec2sArrayType = 12,
			Vec3sArrayType = 13,
			Vec4sArrayType = 14,

			Vec2iArrayType = 15,
			Vec3iArrayType = 16,
			Vec4iArrayType = 17,

			Vec2ubArrayType = 18,
			Vec3ubArrayType = 19,
			Vec4ubArrayType = 20,

			Vec2usArrayType = 21,
			Vec3usArrayType = 22,
			Vec4usArrayType = 23,

			Vec2uiArrayType = 24,
			Vec3uiArrayType = 25,
			Vec4uiArrayType = 26,

			Vec2ArrayType = 27,
			Vec3ArrayType = 28,
			Vec4ArrayType = 29,

			Vec2dArrayType = 30,
			Vec3dArrayType = 31,
			Vec4dArrayType = 32,

			MatrixArrayType = 33,
			MatrixdArrayType = 34,

			CustomArrayType = 35
		};

		Arraylist(Type arrayType = ArrayType, GLuint dataSize = 0, GLenum dataType = 0) :
			_arrayType(arrayType),
			_dataSize(dataSize),
			_dataType(dataType) {}

		Type    getType() const { return _arrayType; }
		GLuint  getDataSize() const { return _dataSize; }
		GLenum  getDataType() const { return _dataType; }

		virtual unsigned int    getElementSize() const = 0;
		virtual const GLvoid*   getDataPointer() const = 0;
		virtual unsigned int    getNumElements() const = 0;

	protected:

		virtual ~Arraylist() {}

		Type     _arrayType;
		GLuint   _dataSize;
		GLenum   _dataType;
	};

	template<typename T, Arraylist::Type ARRAYTYPE, int DataSize, int DataType>
	class TemplateArrayList : public Arraylist
	{
	public:
		TemplateArrayList() :
			_data(NULL),
			_dataIndex(0),
			_dataMaxNum(0),
			_dataGrowNum(256),
			Arraylist(ARRAYTYPE, DataSize, DataType) {}
		
		~TemplateArrayList() 
		{
			if (_data)
			{
				delete[]_data;
				_data = NULL;
			}
			_dataIndex = 0;
			_dataMaxNum = 0;
		}

		TemplateArrayList& operator = (const TemplateArrayList& _array)
		{
			if (_array.getMaxElements() > getMaxElements())
			{
				resize(_array.getMaxElements());
			}
			unsigned int dataSize = _array.getMaxElements()*getElementSize();
			memcpy(_data, _array.getDataPointer(), dataSize);
			_dataIndex = _array.getNumElements();

			return *this;
		}
		T& operator [] (unsigned int pos) {
			return at[pos];
		}

		virtual unsigned int    getElementSize() const {
			return sizeof(ElementDataType);
		}
		virtual const GLvoid*   getDataPointer() const {
			return _data;
		}
		virtual unsigned int    getNumElements() const {
			return _dataIndex;
		}
		virtual unsigned int    getMaxElements() const {
			return _dataMaxNum;
		}
		//销毁
		virtual void            reserve(unsigned int itor)
		{
			if (itor >= _dataIndex || _dataIndex == 0)return;
			unsigned char *dst = (unsigned char *)_data + itor*getElementSize();
			unsigned char *src = (unsigned char *)_data + (itor + 1)*getElementSize();
			unsigned int dataSize = (_dataIndex - itor - 1)*getElementSize();
			memcpy(dst, src, dataSize);
			_dataIndex--;
		}
		//重置Elements大小
		virtual void            resize(unsigned int num)
		{
			if (this->_dataMaxNum == 0 && _data == NULL)
			{
				unsigned int dataSize = num*getElementSize();
				_data = (unsigned char *)malloc(dataSize);
				memset(_data, 0, dataSize);
				_dataMaxNum = num;
			}
			else if (this->_dataMaxNum < num && _data)
			{
				num += _dataGrowNum;//增长个数
				unsigned int dataSize = num*getElementSize();
				unsigned char *objData = (unsigned char *)malloc(dataSize);
				memset(objData, 0, dataSize);

				dataSize = _dataMaxNum*getElementSize();
				unsigned char *src = (unsigned char *)_data;
				memcpy(objData, src, dataSize);
				_data = objData;
				free(src);

				this->_dataMaxNum = num;
			}
		}
		//追加Element
		virtual void            push_back(const T & _t)
		{
			if (_dataIndex == _dataMaxNum)
			{
				resize(_dataMaxNum + _dataGrowNum);
			}
			unsigned char *dst = (unsigned char *)_data + _dataIndex*getElementSize();
			memcpy(dst, &_t, getElementSize());

			_dataIndex++;
		}
		//移除最后一个Element
		virtual void            pop_back() {
			_dataIndex--;
		}
		//插入Element
		virtual void            insert(unsigned int itor, const T & _t) {
			if (itor >= _dataIndex || _dataIndex == 0)return;
			if (_dataIndex == _dataMaxNum)
			{
				resize(_dataMaxNum + _dataGrowNum);
			}
			unsigned char *src = (unsigned char *)_data + itor*getElementSize();
			unsigned int dataSize = (_dataIndex - itor)*getElementSize();
			unsigned char *curData = (unsigned char *)malloc(dataSize);
			memcpy(curData, src, dataSize);

			unsigned char *dst = (unsigned char *)_data + itor*getElementSize();
			memcpy(dst, &_t, getElementSize());

			dst = (unsigned char *)_data + (itor + 1)*getElementSize();
			memcpy(dst, curData, dataSize);
			free(curData);

			_dataIndex++;
		}
		//移除Element
		virtual void            remove(unsigned int itor) {
			if (itor >= _dataIndex || _dataIndex == 0)return;
			unsigned char *dst = (unsigned char *)_data + itor*getElementSize();
			unsigned char *src = (unsigned char *)_data + (itor + 1)*getElementSize();
			unsigned int dataSize = (_dataIndex - itor - 1)*getElementSize();
			memcpy(dst, src, dataSize);

			_dataIndex--;
		}
		//清除Element
		virtual void            clear() {
			_dataIndex = 0;
		}
		//索引
		virtual T&             at(unsigned int pos) {
			T *t = (T *)_data;
			if (pos >= _dataIndex || _dataIndex == 0)return t[_dataMaxNum];
			return t[pos];
		}

		typedef T				ElementDataType;            //类型
	protected:
		GLvoid*					_data;
		GLuint					_dataIndex;
		GLuint					_dataMaxNum;
		GLuint					_dataGrowNum;
	};

	typedef TemplateArrayList<GLbyte, Arraylist::ByteArrayType, 1, GL_BYTE>                 ArraylistByte;
	typedef TemplateArrayList<GLshort, Arraylist::ShortArrayType, 1, GL_SHORT>              ArraylistShort;
	typedef TemplateArrayList<GLint, Arraylist::IntArrayType, 1, GL_INT>                    ArraylistInt;

	typedef TemplateArrayList<GLubyte, Arraylist::UByteArrayType, 1, GL_UNSIGNED_BYTE>      ArraylistUByte;
	typedef TemplateArrayList<GLushort, Arraylist::UShortArrayType, 1, GL_UNSIGNED_SHORT>   ArraylistUShort;
	typedef TemplateArrayList<GLuint, Arraylist::UIntArrayType, 1, GL_UNSIGNED_INT>         ArraylistUInt;
	typedef TemplateArrayList<GLfloat, Arraylist::FloatArrayType, 1, GL_FLOAT>              ArraylistFloat;


	typedef TemplateArrayList<Vec2f, Arraylist::Vec2ArrayType, 2, GL_FLOAT>                 ArraylistVec2;
	typedef TemplateArrayList<Vec3f, Arraylist::Vec3ArrayType, 3, GL_FLOAT>                 ArraylistVec3;
	typedef TemplateArrayList<Vec4f, Arraylist::Vec4ArrayType, 4, GL_FLOAT>                 ArraylistVec4;
	typedef TemplateArrayList<Matrixf, Arraylist::MatrixArrayType, 16, GL_FLOAT>            ArraylistMatrixf;

#ifdef WIN32
	typedef TemplateArrayList<Vec2d, Arraylist::Vec2dArrayType, 2, GL_DOUBLE>                ArraylistVec2d;
	typedef TemplateArrayList<Vec3d, Arraylist::Vec3dArrayType, 3, GL_DOUBLE>                ArraylistVec3d;
	typedef TemplateArrayList<Vec4d, Arraylist::Vec4dArrayType, 4, GL_DOUBLE>                ArraylistVec4d;
	typedef TemplateArrayList<Matrixd, Arraylist::MatrixdArrayType, 16, GL_DOUBLE>           ArraylistMatrixd;
#else
	typedef TemplateArrayList<Vec2d, Arraylist::Vec2dArrayType, 2, GL_FIXED>                ArraylistVec2d;
	typedef TemplateArrayList<Vec3d, Arraylist::Vec3dArrayType, 3, GL_FIXED>                ArraylistVec3d;
	typedef TemplateArrayList<Vec4d, Arraylist::Vec4dArrayType, 4, GL_FIXED>                ArraylistVec4d;
	typedef TemplateArrayList<Matrixd, Arraylist::MatrixdArrayType, 16, GL_FIXED>           ArraylistMatrixd;
#endif



}

#endif
