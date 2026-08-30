#include "timer.h"

void timer_start(Timer *t) {
    clock_gettime(CLOCK_MONOTONIC, &t->inicio);
}

void timer_stop(Timer *t) {
    clock_gettime(CLOCK_MONOTONIC, &t->fim);
}

double timer_elapsed_seconds(Timer *t) {
    double segundos = (double)(t->fim.tv_sec - t->inicio.tv_sec);
    double nanos = (double)(t->fim.tv_nsec - t->inicio.tv_nsec);
    return segundos + nanos / 1e9;
}