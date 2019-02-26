//
// Created by 안재찬 on 15/11/2018.
//

#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"

#define PROBABILITY 0.5
#define MAX_LEVEL 25

typedef struct node {
    uint64_t key;
    uint64_t value;

    struct node *right;
    struct node *left;
    struct node *up;
    struct node *down;
} node_t;

typedef struct skiplist {
    struct node *root; // top left corner node.

    uint64_t size;

    uint64_t min;
    uint64_t max;
} skiplist_t;

skiplist_t *init_skip_list();

node_t *init_node(uint64_t key, uint64_t value);

node_t *insert(skiplist_t *list, uint64_t key, uint64_t value);

node_t *find(skiplist_t *list, uint64_t key);

void clear_nodes(skiplist_t *list);

void print_list(skiplist_t *list);

#endif //SKIPLIST_SKIPLIST_H
