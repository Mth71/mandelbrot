#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct {
    struct timespec inicio;
    struct timespec fim;
} Timer;

void timer_start(Timer *t);
void timer_stop(Timer *t);
double timer_elapsed_seconds(Timer *t);

#endif