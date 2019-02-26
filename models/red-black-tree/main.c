#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "rbtree.h"

#define BILLION 1000000000ULL

struct timespec start, end;
double elapsed_time;

int main(int argc, char **argv) {
    FILE *ifp;
    FILE *ofp;
    char *ifname;
    char order;
    uint64_t key, val;

    node_t *root = NULL;
    node_f result;

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

    do {
        order = (char) getc(ifp);
        switch (order) {
            case 'I':
                fscanf(ifp, "%lld %lld\n", &key, &val);
                result = find(root, key);

                if (result.node != NULL) {
                    fprintf(ofp, "Found (%lld, %lld) update v=%lld\n", result.node->key, result.node->val, val);
                    result.node->val = val;
                } else {
                    root = insert(root, key, val);
                    fprintf(ofp, "Inserted (%lld, %lld)\n", key, val);
                }
                break;
            case 'F':
                fscanf(ifp, "%lld\n", &key);
                result = find(root, key);
                if (result.node == NULL) {
                    fprintf(ofp, "Not Found\n");
                } else {
                    fprintf(ofp, "Found (%lld, %lld) on d=%lld with c=%s\n", result.node->key,
                            result.node->val, result.d, result.node->color == BLACK ? "black" : "red");
                }
                break;
            case 'P':
                print_tree(ofp, root);
                fputs("\n", ofp);
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

    delete_tree(root);

    return 0;
}