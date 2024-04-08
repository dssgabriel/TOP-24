/**
 * \file timer.h
 **/

#ifndef TOP_TIMER_H
#define TOP_TIMER_H

#define _GNU_SOURCE

#include "../../types.h"

#include <sys/time.h>

#define TIMER_INIT int64_t t_start, t_end;
#define TIMER_START t_start = usecs();
#define TIMER_END t_end = usecs();
#define TIMER_RESULT_IN_SECONDS (double)(t_end - t_start) / 1e+6
#define TIMER_PRINT                                                                                \
    printf(                                                                                        \
        "ELAPSED TIME:  %.3lf s\nAVERAGE:       %.3lf ns\n",                                       \
        TIMER_RESULT_IN_SECONDS,                                                                   \
        TIMER_RESULT_IN_SECONDS * 1e+9 / (double)repetitions                                       \
    );

static inline int64_t usecs(void) {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

#endif // TOP_TIMER_H
