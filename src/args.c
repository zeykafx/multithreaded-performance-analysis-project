#include "../headers/args.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>


/* 
 * sets the default options
 */
static void set_default_options(options_t *options) {
    options->number_philosophers = 0;

    options->number_consumers = 0;
    options->number_producers = 0;

    options->number_readers = 0;
    options->number_writers = 0;
    options->verbose = false;
}

static void usage() {
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "    [OPTIONS - You must set the number of threads for at least one option]\n");
    fprintf(stderr, "    -v verbose: shows additionnal information\n");
    fprintf(stderr, "    -N number of philosophers (default: 0): set the number of philosophers (threads) that will run concurrently\n");
    fprintf(stderr, "    -c number of consumers (default: 0): set the number of consumer threads\n");
    fprintf(stderr, "    -p number of producers (default: 0): set the number of producer threads\n");
    fprintf(stderr, "    -r number of readers (default: 0): set the number of reader threads\n");
    fprintf(stderr, "    -r number of writers (default: 0): set the number of writer threads\n");
}


/* 
 * parses the command line arguments
 */
int options_parser(int argc, char *argv[], options_t *options) {
    memset(options, 0, sizeof(options_t));

    set_default_options(options);


    int opt;
    while ((opt = getopt(argc, argv, "N:c:p:r:w:v")) != -1) {
        switch (opt) {
            case 'N':
                options->number_philosophers = atoi(optarg);
                if (options->number_philosophers == 0) {
                    fprintf(stderr, "The number of philosophers must be greater than 0 (each philosopher is a thread), got: %s", optarg);
                    return -1;
                }
                break;
            case 'c':
                options->number_consumers = atoi(optarg);
                if (options->number_consumers == 0) {
                    fprintf(stderr, "The number of consumers must be greater than 0 (each consumer is a thread), got: %s", optarg);
                    return -1;
                }
                break;
            case 'p':
                options->number_producers = atoi(optarg);
                if (options->number_consumers == 0) {
                    fprintf(stderr, "The number of producers must be greater than 0 (each producer is a thread), got: %s", optarg);
                    return -1;
                }
                break;
            case 'r':
                options->number_readers = atoi(optarg);
                if (options->number_readers == 0) {
                    fprintf(stderr, "The number of readers must be greater than 0 (each reader is a thread), got: %s", optarg);
                    return -1;
                }
                break;
            case 'w':
                options->number_writers = atoi(optarg);
                if (options->number_writers == 0) {
                    fprintf(stderr, "The number of writers must be greater than 0 (each writer is a thread), got: %s", optarg);
                    return -1;
                }
                break;
            case 'v':
                options->verbose = true;
                break;
            default: 
                usage();
                break;
        }
    }

    // show an error message if no thread number was provided (even if verbose is enabled)
    if (optind == 1 || (options->verbose && optind == 2)) {
        fprintf(stderr, "You must set the number of threads for at least one of the options to run the program.\n");
        usage();
        exit(EXIT_FAILURE);
    }


    return 0;
}