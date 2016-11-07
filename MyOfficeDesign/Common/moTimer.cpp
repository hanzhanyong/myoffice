#include <stdio.h>
#include <string>

#include "moTimer.h"
#include <iostream>
//#include <Notify>

using namespace MyOffice;

// follows are the constructors of the Timer class, once version
// for each OS combination.  The order is WIN32, FreeBSD, Linux, IRIX,
// and the rest of the world.
//
// all the rest of the timer methods are implemented within the header.


Timer* Timer::instance()
{
    static Timer s_timer;
    return &s_timer;
}

#ifdef WIN32

    #include <sys/types.h>
    #include <fcntl.h>
    #include <windows.h>
    #include <winbase.h>
    Timer::Timer()
    {
        LARGE_INTEGER frequency;
        if(QueryPerformanceFrequency(&frequency))
        {
            _secsPerTick = 1.0/(double)frequency.QuadPart;
        }
        else
        {
            _secsPerTick = 1.0;
			std::cout<<"Error: Timer::Timer() unable to use QueryPerformanceFrequency, "<<std::endl;
            std::cout<<"timing code will be wrong, Windows error code: "<<GetLastError()<<std::endl;
        }
        
        setStartTick();        
    }

    Timer_t Timer::tick() const
    {
        LARGE_INTEGER qpc;
        if (QueryPerformanceCounter(&qpc))
        {
            return qpc.QuadPart;
        }
        else
        {
            std::cout<<"Error: Timer::Timer() unable to use QueryPerformanceCounter, "<<std::endl;
            std::cout<<"timing code will be wrong, Windows error code: "<<GetLastError()<<std::endl;
            return 0;
        }
    }

#else
    #include <unistd.h>

    Timer::Timer( void )
    {
        _secsPerTick = (1.0 / (double) 1000000);

        setStartTick();        
    }

    #if defined(_POSIX_TIMERS) && ( _POSIX_TIMERS > 0 ) && defined(_POSIX_MONOTONIC_CLOCK)
        #include <time.h>

        Timer_t Timer::tick() const
        {
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            return ((mapf::Timer_t)ts.tv_sec)*1000000+(mapf::Timer_t)ts.tv_nsec/1000;
        }
    #else
        #include <sys/time.h>

        Timer_t Timer::tick() const
        {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            return ((mapf::Timer_t)tv.tv_sec)*1000000+(mapf::Timer_t)tv.tv_usec;
        }
    #endif

#endif
