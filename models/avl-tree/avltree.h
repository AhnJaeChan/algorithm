//
// Created by 안재찬 on 20/11/2018.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "util.h"

typedef struct node {
    uint64_t key;
    uint64_t val;

    struct node *left;
    struct node *right;

    int height;
} node_t;

// Struct for node finding. Originally implemented find() recursively
// but changed it to iterative just to decrease the recursive call and variable passing.
typedef struct node_found {
    node_t *node;
    uint64_t d;
} node_f;

node_t *init_node(uint64_t key, uint64_t val);

int get_height(node_t *node);

node_t *left_rotate(node_t *node);

node_t *right_rotate(node_t *node);

node_t *insert(node_t *cur_node, uint64_t key, uint64_t val);

node_f find(node_t *cur_node, uint64_t key);

void print_tree(FILE *ofp, node_t *cur_node);

void delete_tree(node_t *root_node);

#endif //AVLTREE_AVLTREE_H
