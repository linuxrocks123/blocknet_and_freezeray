#include <time.h>
#include <sys/time.h>
#include <dlfcn.h>

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
     int (*real_gettimeofday)(struct timeval *, struct timezone *) = dlsym(((void *) -1l),"gettimeofday");
     real_gettimeofday(tv,tz);
     tv->tv_sec=1392546206+tv->tv_sec%3600;
     return 0;
}

int gettime(struct timespec* tv)
{
    return gettimeofday((struct timeval*)(tv),(void*)(0));
}

int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
     if(clk_id==CLOCK_REALTIME)
          return gettime(tp);
     else
     {
          int (*real_clock_gettime)(clockid_t,struct timespec*) = dlsym(((void *) -1l),"clock_gettime");
          return real_clock_gettime(clk_id,tp);
     }

     return -1;
}
