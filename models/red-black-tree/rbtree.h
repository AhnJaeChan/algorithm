//
// Created by 안재찬 on 20/11/2018.
//

#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define RED 1
#define BLACK 0

typedef struct node {
    uint64_t key;
    uint64_t val;

    struct node *parent;

    struct node *left;
    struct node *right;

    int color; // RED or BLACK
} node_t;

// Struct for node finding. Originally implemented find() recursively
// but changed it to iterative just to decrease the recursive call and variable passing.
typedef struct node_found {
    node_t *node;
    uint64_t d;
} node_f;

node_t *init_node(uint64_t key, uint64_t val);

void left_rotate(node_t *node);

void right_rotate(node_t *node);

node_t *bst_insert(node_t *root_node, node_t *new_node);

node_t *fix_tree(node_t *root_node, node_t *cur_node);

node_t *insert(node_t *root, uint64_t key, uint64_t val);

node_f find(node_t *cur_node, uint64_t key);

void print_tree(FILE *ofp, node_t *cur_node);

void delete_tree(node_t *root_node);


#endif //RBTREE_RBTREE_H
