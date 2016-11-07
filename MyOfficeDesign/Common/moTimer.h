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

#ifndef MYOFFICEDESIGN_TIMER_H_
#define MYOFFICEDESIGN_TIMER_H_
#include "moExport.h"
namespace MyOffice {

#if defined(_MSC_VER)
	typedef __int64 Timer_t;
#else
	typedef unsigned long long Timer_t;
#endif

	class MO_EXPORT_DLL Timer {
	public:
		Timer();
		~Timer() {}

		static Timer* instance();

		/** Get the timers tick value.*/
		Timer_t tick() const;

		/** Set the start.*/
		void setStartTick() { _startTick = tick(); }
		void setStartTick(Timer_t t) { _startTick = t; }
		Timer_t getStartTick() const { return _startTick; }


		/** Get elapsed time in seconds.*/
		inline double time_s() const { return delta_s(_startTick, tick()); }

		/** Get elapsed time in milliseconds.*/
		inline double time_m() const { return delta_m(_startTick, tick()); }

		/** Get elapsed time in microseconds.*/
		inline double time_u() const { return delta_u(_startTick, tick()); }

		/** Get elapsed time in nanoseconds.*/
		inline double time_n() const { return delta_n(_startTick, tick()); }

		/** Get the time in seconds between timer ticks t1 and t2.*/
		inline double delta_s( Timer_t t1, Timer_t t2 ) const { return (double)(t2 - t1)*_secsPerTick; }

		/** Get the time in milliseconds between timer ticks t1 and t2.*/
		inline double delta_m( Timer_t t1, Timer_t t2 ) const { return delta_s(t1,t2)*1e3; }

		/** Get the time in microseconds between timer ticks t1 and t2.*/
		inline double delta_u( Timer_t t1, Timer_t t2 ) const { return delta_s(t1,t2)*1e6; }

		/** Get the time in nanoseconds between timer ticks t1 and t2.*/
		inline double delta_n( Timer_t t1, Timer_t t2 ) const { return delta_s(t1,t2)*1e9; }

		/** Get the the number of seconds per tick. */
		inline double getSecondsPerTick() const { return _secsPerTick; }

	protected :
		Timer_t _startTick;
		double  _secsPerTick;
	};

	/** Helper class for timing sections of code. */
	class MO_EXPORT_DLL ElapsedTime
	{
	public:
		inline ElapsedTime(double* elapsedTime, Timer* timer = 0):
		_time(elapsedTime)
		{
			init(timer);
		}

		inline ElapsedTime(Timer* timer = 0):
		_time(0)
		{
			init(timer);
		}

		inline ~ElapsedTime()
		{
			finish();
		}

		inline void reset()
		{
			_startTick = _timer->tick();
		}

		/** elapsed time in seconds. */
		inline double elapsedTime() const
		{
			return _timer->delta_s(_startTick, _timer->tick());
		}

		/** elapsed time in milliseconds. */
		inline double elapsedTime_m() const
		{
			return _timer->delta_m(_startTick, _timer->tick());
		}

		/** elapsed time in microseconds. */
		inline double elapsedTime_u() const
		{
			return _timer->delta_u(_startTick, _timer->tick());
		}

		/** elapsed time in nanoseconds. */
		inline double elapsedTime_n() const
		{
			return _timer->delta_n(_startTick, _timer->tick());
		}

		inline void finish()
		{
			Timer_t endTick = _timer->tick();
			if (_time) *_time += _timer->delta_s(_startTick, endTick);
			_startTick = endTick;
		}

	protected:

		inline void init(Timer* timer)
		{
			if (timer) _timer = timer;
			else _timer = Timer::instance();

			_startTick = _timer->tick();
		}

		double* _time;
		Timer*  _timer;
		Timer_t _startTick;

	};
}
#endif
