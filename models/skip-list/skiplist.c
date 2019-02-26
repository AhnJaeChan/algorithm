//
// Created by 안재찬 on 17/11/2018.
//

#include "skiplist.h"

skiplist_t *init_skip_list() {
    skiplist_t *l;

    l = (skiplist_t *) malloc(sizeof(skiplist_t));
    l->root = NULL;
    l->size = 0;
    l->min = 0;
    l->max = 0;

    return l;
}

node_t *init_node(uint64_t key, uint64_t value) {
    node_t *node = (node_t *) malloc(sizeof(node_t));
    node->key = key;
    node->value = value;

    node->up = NULL;
    node->down = NULL;
    node->right = NULL;
    node->left = NULL;

    return node;
}

node_t *insert(skiplist_t *list, uint64_t key, uint64_t value) {
    node_t *cur_node;
    node_t *new_node;
    int new_height = 0;

    node_t *path_nodes[MAX_LEVEL];
    int level = 0;

    int i;

    // If the list is empty, initial insert
    if (list->root == NULL) {
        list->root = init_node(key, value);
        list->size++;
        list->min = key;
        list->max = key;

        cur_node = list->root;
        for (i = 0; i < MAX_LEVEL - 1; i++) {
            cur_node->down = init_node(key, value);
            cur_node->down->up = cur_node;
            cur_node = cur_node->down;
        }
        return list->root;
    }

    // Check if the key is less/greater than min/max
    if (key < list->min) {
        // insert to the front
        cur_node = list->root;

        if (list->min == list->max) {
            for (i = 0; i < MAX_LEVEL; i++) {
                cur_node->left = init_node(key, value);
                cur_node->left->right = cur_node;
                cur_node = cur_node->down;
            }

            cur_node = list->root;
            for (i = 0; i < MAX_LEVEL - 1; i++) {
                cur_node->left->down = cur_node->down->left;
                cur_node->down->left->up = cur_node->left;
                cur_node = cur_node->down;
            }

            list->root = list->root->left;
            list->min = key;
            return list->root;
        }

        while (cur_node->down != NULL) {
            cur_node->key = key;
            cur_node->value = value;
            cur_node = cur_node->down;
        }
        cur_node->key = key;
        cur_node->value = value;

        new_node = init_node(list->root->key, list->root->value);
        new_node->left = cur_node;
        if (cur_node->right != NULL) {
            new_node->right = cur_node->right;
            cur_node->right->left = new_node;
        }
        cur_node->right = new_node;
        list->min = key;
        return cur_node;
    } else if (key > list->max) {
        // Same as min but backwards
        cur_node = list->root;

        if (list->min == list->max) {
            for (i = 0; i < MAX_LEVEL; i++) {
                cur_node->right = init_node(key, value);
                cur_node->right->left = cur_node;
                cur_node = cur_node->down;
            }

            cur_node = list->root;
            for (i = 0; i < MAX_LEVEL - 1; i++) {
                cur_node->right->down = cur_node->down->right;
                cur_node->down->right->up = cur_node->right;
                cur_node = cur_node->down;
            }
            list->max = key;
            return cur_node->right;
        }

        // Go to the tail
        while (cur_node->right != NULL) {
            cur_node = cur_node->right;
        }

        new_node = init_node(cur_node->key, cur_node->value);

        while (cur_node->down != NULL) {
            cur_node->key = key;
            cur_node->value = value;
            cur_node = cur_node->down;
        }
        cur_node->key = key;
        cur_node->value = value;

        new_node->right = cur_node;
        if (cur_node->left != NULL) {
            new_node->left = cur_node->left;
            cur_node->left->right = new_node;
        }
        cur_node->left = new_node;
        list->max = key;
        return cur_node;
    } else if (key == list->min || key == list->max) {
        cur_node = list->root;

        while (cur_node->key != key) {
            cur_node = cur_node->right;
        }
        new_node = init_node(cur_node->key, cur_node->value); // Just for returning

        while (cur_node != NULL) {
            cur_node->value = value;
            cur_node = cur_node->down;
        }
        return new_node;
    } else {
        // insert to somewhere in the middle
        cur_node = list->root;

        while (level < MAX_LEVEL) {
            if (cur_node->right->key < key) {
                cur_node = cur_node->right;
            } else {
                path_nodes[level++] = cur_node;
                cur_node = cur_node->down;
            }
        }

        cur_node = path_nodes[MAX_LEVEL - 1];
        while (cur_node->key < key) {
            cur_node = cur_node->right;
        }
        path_nodes[MAX_LEVEL - 1] = cur_node->left;

        if (cur_node->key == key) {
            new_node = init_node(cur_node->key, cur_node->value); // For return

            // Override value
            while (cur_node->up != NULL) {
                cur_node->value = value;
                cur_node = cur_node->up;
            }
            cur_node->value = value;
            return new_node;
        }

        // #TODO: Change rand() to different PRNG
        while ((double) rand() / RAND_MAX < PROBABILITY) {
            new_height++;
        }

        if (new_height > MAX_LEVEL) {
            new_height = MAX_LEVEL;
        }

        new_node = init_node(key, value);

        cur_node = path_nodes[MAX_LEVEL - 1];

        new_node->right = cur_node->right;
        new_node->left = cur_node;
        cur_node->right->left = new_node;
        cur_node->right = new_node;

        for (i = 1; i < new_height; i++) {
            new_node = init_node(key, value);

            cur_node = path_nodes[MAX_LEVEL - 1 - i];

            new_node->right = cur_node->right;
            new_node->left = cur_node;
            cur_node->right->left = new_node;
            cur_node->right = new_node;

            new_node->down = path_nodes[MAX_LEVEL - i]->right;
            path_nodes[MAX_LEVEL - i]->right->up = new_node;
        }

        list->size++;
        return new_node;
    }
}

node_t *find(skiplist_t *list, uint64_t key) {
    node_t *cur_node = list->root;
    node_t *last_node = list->root;
    int level = 0;

    if (cur_node == NULL) {
        // Empty List
        return NULL;
    }

    if (key > list->max || key < list->min) {
        return NULL;
    }

    while (level < MAX_LEVEL && cur_node->right != NULL) {
        if (cur_node->right->key < key) {
            cur_node = cur_node->right;
        } else {
            last_node = cur_node;
            cur_node = cur_node->down;
            level++;
        }
    }

    cur_node = last_node;
    while (cur_node->key < key) {
        cur_node = cur_node->right;
    }

    if (cur_node->key == key) {
        return cur_node;
    } else {
        return NULL;
    }
}

void clear_nodes(skiplist_t *list) {
    int i;
    node_t *cur_node = list->root;
    node_t *next_node;
    node_t *level_heads[MAX_LEVEL];

    if (cur_node == NULL) return;

    for (i = 0; i < MAX_LEVEL; i++) {
        level_heads[i] = cur_node;
        cur_node = cur_node->down;
    }

    for (i = 0; i < MAX_LEVEL; i++) {
        cur_node = level_heads[i];
        while (cur_node != NULL) {
            next_node = cur_node->right;
            free(cur_node);
            cur_node = next_node;
        }
    }
}

void print_list(skiplist_t *list) {
    int i;
    node_t *cur_level_root = list->root;
    node_t *cur_node;

    for (i = 0; i < MAX_LEVEL; i++) {
        printf("[Lv.%2d]: ", MAX_LEVEL - i);
        cur_node = cur_level_root;
        while (cur_node->right != NULL) {
            printf("(%lld, %lld) -> ", cur_node->key, cur_node->value);
            cur_node = cur_node->right;
        }
        printf("(%lld, %lld)\n", cur_node->key, cur_node->value);

        cur_level_root = cur_level_root->down;
    }
}