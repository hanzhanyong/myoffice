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

#ifndef MYOFFICEDESIGN_OPENGL
#define MYOFFICEDESIGN_OPENGL
 
#ifdef WIN32
//	#define MAPF_GL1_AVAILABLE
	#define MAPF_GL2_AVAILABLE
//	#define MAPF_GL3_AVAILABLE
#else
//	#define MAPF_GLES1_AVAILABLE
	#define MAPF_GLES2_AVAILABLE
//	#define MAPF_GLES3_AVAILABLE
#endif

#if defined(MAPF_GL3_AVAILABLE)
    #define GL3_PROTOTYPES 1
    #define GL_GLEXT_PROTOTYPES 1
#endif


#if defined(MAPF_GLES1_AVAILABLE)

    #ifdef __APPLE__
        #include <OpenGLES/ES1/gl.h>
    #else
        #include <GLES/gl.h>
    #endif
#endif

#if defined(MAPF_GLES2_AVAILABLE)

    #ifdef __APPLE__
        #include <OpenGLES/ES2/gl.h>
    #else
         #include <GLES2/gl2.h>
    #endif


#else

    #ifndef WIN32

        // Required for compatibility with glext.h sytle function definitions of 
        // OpenGL extensions, such as in src/osg/Point.cpp.
        #ifndef APIENTRY
            #define APIENTRY
        #endif

    #else // WIN32

        #if defined(__CYGWIN__) || defined(__MINGW32__)

            #ifndef APIENTRY
                 #define GLUT_APIENTRY_DEFINED
                 #define APIENTRY __stdcall
            #endif
             // XXX This is from Win32's <windef.h> 
            #ifndef CALLBACK
                #define CALLBACK __stdcall
            #endif

        #else // ! __CYGWIN__

            // Under Windows avoid including <windows.h>
            // to avoid name space pollution, but Win32's <GL/gl.h> 
            // needs APIENTRY and WINGDIAPI defined properly. 
            // XXX This is from Win32's <windef.h> 
            #ifndef APIENTRY
                #define GLUT_APIENTRY_DEFINED
                #if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
                    #define WINAPI __stdcall
                    #define APIENTRY WINAPI
                #else
                    #define APIENTRY
                #endif
            #endif

             // XXX This is from Win32's <windef.h> 
            #ifndef CALLBACK
                #if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
                    #define CALLBACK __stdcall
                #else
                    #define CALLBACK
                #endif
            #endif

        #endif // __CYGWIN__

        // XXX This is from Win32's <wingdi.h> and <winnt.h> 
        #ifndef WINGDIAPI
            #define GLUT_WINGDIAPI_DEFINED
            #define DECLSPEC_IMPORT __declspec(dllimport)
            #define WINGDIAPI DECLSPEC_IMPORT
        #endif
        
        // XXX This is from Win32's <ctype.h>
        #if !defined(_WCHAR_T_DEFINED) && !(defined(__GNUC__)&&((__GNUC__ == 3)||(__GNUC__ == 4)))
            typedef unsigned short wchar_t;
            #define _WCHAR_T_DEFINED
        #endif

    #endif // WIN32

    #if defined(MAPF_GL3_AVAILABLE)

        #define GL3_PROTOTYPES 1
        #include <GL3/gl3.h>

    #else
        #ifndef __gl_h_
            #ifdef __APPLE__
                #include <OpenGL/gl.h>
            #else
                #include <GL/gl.h>
            #endif
        #endif
    #endif

    #ifndef GL_APIENTRY
        #define GL_APIENTRY APIENTRY
    #endif // GL_APIENTRY

#endif

#include "moGLDefine.h"


// add defines for OpenGL targets that don't define them, just to ease compatibility across targets
#ifndef GL_DOUBLE
    #define GL_DOUBLE 0x140A
    typedef double GLdouble;
#endif

#ifndef GL_INT
    #define GL_INT 0x1404
#endif

#ifndef GL_UNSIGNED_INT
    #define GL_UNSIGNED_INT 0x1405
#endif

#ifndef GL_NONE
    // OpenGL ES1 doesn't provide GL_NONE
    #define GL_NONE 0x0
#endif

#if defined(MAPF_GLES1_AVAILABLE) || defined(MAPF_GLES2_AVAILABLE)
    //GLES defines (OES)
    #define GL_RGB8_OES                                             0x8051
    #define GL_RGBA8_OES                                            0x8058
#endif

#if defined(MAPF_GLES1_AVAILABLE) || defined(MAPF_GLES2_AVAILABLE) || defined(MAPF_GL3_AVAILABLE)
    #define GL_POLYGON                         0x0009
    #define GL_QUADS                           0x0007
    #define GL_QUAD_STRIP                      0x0008
#endif

#if defined(MAPF_GL3_AVAILABLE)
    #define GL_LUMINANCE                      0x1909
    #define GL_LUMINANCE_ALPHA                0x190A
#endif

#endif