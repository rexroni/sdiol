#include "time_util.h"

struct timeval timeval_now(){
    struct timespec now_timespec;
    clock_gettime(CLOCK_REALTIME, &now_timespec);
    struct timeval now;
    TIMESPEC_TO_TIMEVAL(&now, &now_timespec);
    return now;
}

// helper functions for difference of two struct timeval's (compute "a - b")
long msec_diff(struct timeval a, struct timeval b){
    long diff = (a.tv_usec / 1000) - (b.tv_usec / 1000);
    return diff + (a.tv_sec - b.tv_sec) * 1000;
}
struct timeval timeval_diff(struct timeval a, struct timeval b){
    long usec_diff = a.tv_usec - b.tv_usec;
    long usec_mod = usec_diff % 1000000;
    if(usec_mod < 0) usec_mod += 1000000;
    struct timeval out = {.tv_usec=usec_mod};
    out.tv_sec = a.tv_sec - b.tv_sec + (usec_diff - usec_mod) / 1000000;
    return out;
}

struct timeval msec_after(struct timeval tv, long millis){
    // handle integer seconds
    tv.tv_sec += millis / 1000;
    // calculate msec
    long msec = (millis % 1000) + (tv.tv_usec / 1000);
    // handle msec overflow
    tv.tv_sec += msec > 1000;
    tv.tv_usec = (tv.tv_usec % 1000) + (msec % 1000) * 1000;
    return tv;
}
