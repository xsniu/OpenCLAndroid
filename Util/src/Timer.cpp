#include "Timer.h"

#include "config.h"
#include <unistd.h>


Timer::Timer(LogPriority level)
{
    memset(this, 0, sizeof(Timer));
    level_ = level;
}

Timer::~Timer() 
{
}

void Timer::Tic()
{
    if(LOG_LEVEL <= level_)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_);
    }
}

void Timer::Toc()
{
    if(LOG_LEVEL <= level_)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &end_);
    }
}

double Timer::GetElapsedTime() // in ms
{
    if(LOG_LEVEL <= level_)
    {
        timespec temp;
        if ((end_.tv_nsec - start_.tv_nsec) < 0) {
            temp.tv_sec = end_.tv_sec - start_.tv_sec - 1;
            temp.tv_nsec = 1000000000 + end_.tv_nsec - start_.tv_nsec;
        }
        else {
            temp.tv_sec = end_.tv_sec - start_.tv_sec;
            temp.tv_nsec = end_.tv_nsec - start_.tv_nsec;
        }
        return (1000.0 * temp.tv_sec + (double) temp.tv_nsec / 1000000);
    }
    return 0.0;
}