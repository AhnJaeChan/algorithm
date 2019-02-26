#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>

#include "skiplist.h"

#define BILLION 1000000000ULL

struct timespec start, end;
double elapsed_time;

int main(int argc, char **argv) {
    FILE *ifp;
    FILE *ofp;
    char *ifname;
    char order;
    uint64_t key, value;

    skiplist_t *l;
    node_t *result;

    clock_gettime(CLOCK_MONOTONIC, &start);

    if (argc < 2) {
        printf("[Error]: Please check your arguments\n");
        return 1;
    }

    ifname = argv[1];
    ifp = fopen(ifname, "r");
    ofp = fopen("output.txt", "w");

    if (!ifp) {
        printf("[Error]: File open failure.\n");
        return 2;
    }

    srand(time(NULL));

    l = init_skip_list();

    do {
        order = (char) getc(ifp);
        switch (order) {
            case 'I':
                fscanf(ifp, "%lld %lld\n", &key, &value);
                result = insert(l, key, value);

                if (result->value == value) {
                    fprintf(ofp, "Inserted (%lld, %lld)\n", key, value);
                } else {
                    fprintf(ofp, "Found (%lld, %lld) update v=%lld\n", result->key, result->value, value);
                }
                break;
            case 'F':
                fscanf(ifp, "%lld\n", &key);
                result = find(l, key);
                if (result == NULL) {
                    fprintf(ofp, "Not Found\n");
                } else {
                    fprintf(ofp, "Found (%lld, %lld)\n", result->key, result->value);
                }
                break;
            case 'P':
                break;
            case 'Q':
                fclose(ifp);
                fclose(ofp);
                break;
            default:
                break;
        }
    } while (order != EOF);

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_nsec - start.tv_nsec) + (end.tv_sec - start.tv_sec) * BILLION; // calculate time (unit: ns)
    printf("Elapsed time: %lf (s)\n", elapsed_time / 1000000000.0);

    clear_nodes(l);
    free(l);

    return 0;
}
