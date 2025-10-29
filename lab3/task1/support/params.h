#ifndef _PARAMS_H_
#define _PARAMS_H_

#include "common.h"

typedef struct Params {
    unsigned int   input_size;
    int   n_warmup;
    int   n_reps;
    int   n_dpus;
}Params;

static void usage() {
    fprintf(stderr,
        "\nUsage:  ./program [options]"
        "\n"
        "\nGeneral options:"
        "\n    -h        help"
        "\n    -w <W>    # of untimed warmup iterations (default=0)"
        "\n    -e <E>    # of timed repetition iterations (default=1)"
        "\n    -d <D>    # of dpus (default=1)"
        "\n"
        "\nWorkload-specific options:"
        "\n    -i <I>    input size (default=131072 elements=1 MB)"
        "\n");
}

struct Params input_params(int argc, char **argv) {
    struct Params p;
    p.input_size    = 131072;
    p.n_warmup      = 0;
    p.n_reps        = 1;
    p.n_dpus        = 1;

    int opt;
    while((opt = getopt(argc, argv, "hi:w:e:d:")) >= 0) {
        switch(opt) {
        case 'h':
        usage();
        exit(0);
        break;
        case 'i': p.input_size    = atoi(optarg); break;
        case 'w': p.n_warmup      = atoi(optarg); break;
        case 'e': p.n_reps        = atoi(optarg); break;
        case 'd': p.n_dpus        = atoi(optarg); break;
        default:
            fprintf(stderr, "\nUnrecognized option!\n");
            usage();
            exit(0);
        }
    }
    assert(p.n_dpus > 0 && "Invalid # of dpus!");

    return p;
}
#endif
