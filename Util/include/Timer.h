#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>

typedef enum  LogPriority {
    LOG_UNKNOWN = 0,
    LOG_VERBOSE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
}LogPriority;

class Timer
{
    struct timespec start_;
    struct timespec end_;
    LogPriority  level_ {LOG_ERROR};  // default: highest level 
public:
    // Timer();
    Timer(LogPriority level);   // 
    ~Timer();

    void Tic();  // record start time
    void Toc();  // record end time
    double GetElapsedTime(); // in ms
};
#endif