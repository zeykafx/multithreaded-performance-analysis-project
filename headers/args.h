#pragma once

#include <stdbool.h>

typedef struct options {
    int number_philosophers;
    int number_producers;
    int number_consumers;
    int number_readers;
    int number_writers;
    int number_test_and_set_lock_threads;
    int number_test_and_test_and_set_threads;
    int number_sem_test_threads;

    bool running_problems_with_pthread_sync;
    bool verbose;
} options_t;

int options_parser(int argc, char *argv[], options_t *options);
