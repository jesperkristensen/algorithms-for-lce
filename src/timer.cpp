#include "timer.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

// returns seconds.
double gettime() {
#ifdef _WIN32
    __int64 t, f;
    QueryPerformanceFrequency((LARGE_INTEGER *)&f);
    QueryPerformanceCounter((LARGE_INTEGER *)&t);
    return (double)t / (double)f;
#else
    struct timeval s;
    gettimeofday(&s, 0);
    return (double)s.tv_sec + (double)s.tv_usec / 1000000;
#endif
}
