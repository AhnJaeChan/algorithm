//
// Created by 안재찬 on 20/11/2018.
//

#include "avltree.h"

node_t *init_node(uint64_t key, uint64_t val) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    new_node->key = key;
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

int get_height(node_t *node) {
    return node == NULL ? 0 : node->height;
}

node_t *left_rotate(node_t *node) {
    // 1. Take nodes needed for rotation
    node_t *right_child = node->right;
    node_t *mid_sub_tree = right_child->left;

    // 2. Left rotate the (sub)tree
    right_child->left = node;
    node->right = mid_sub_tree;

    // 3. Set the new height
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    right_child->height = max(get_height(right_child->left), get_height(right_child->right)) + 1;

    return right_child; // New top node after rotation.
}

node_t *right_rotate(node_t *node) {
    // 1. Take nodes needed for rotation
    node_t *left_child = node->left;
    node_t *mid_sub_tree = left_child->right;

    // 2. Right rotate the (sub)tree
    left_child->right = node;
    node->left = mid_sub_tree;

    // 3. Set the new height
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    left_child->height = max(get_height(left_child->left), get_height(left_child->right)) + 1;

    return left_child; // New top node after rotation.
}

node_t *insert(node_t *cur_node, uint64_t key, uint64_t val) {
    if (cur_node == NULL) {
        return init_node(key, val);
    }

    // 1. Same as BST insertion, recursively call insert by checking the key
    if (key < cur_node->key) {
        cur_node->left = insert(cur_node->left, key, val);
    } else if (key > cur_node->key) {
        cur_node->right = insert(cur_node->right, key, val);
    } else {
        // Duplicated keys are updated with the current value.
        // * Never called since I've changed the implementation of duplicated key insertion to
        // 1. Check if the key already exist
        // 2. If it does, fix the value at that point.
        cur_node->val = val;
        return cur_node;
    }

    // 2. Calculate the new height
    cur_node->height = max(get_height(cur_node->left), get_height(cur_node->right)) + 1;

    // |Left - Right| should not be greater than 1. (AVL trees property!)
    int height_delta = get_height(cur_node->left) - get_height(cur_node->right);

    if (height_delta > 1) { // [L]eft larger than Right
        if (key < cur_node->left->key) { // LL
            return right_rotate(cur_node);
        } else { // LR
            cur_node->left = left_rotate(cur_node->left);
            return right_rotate(cur_node);
        }
    } else if (height_delta < -1) { // [R]ight larger than Left
        if (key > cur_node->right->key) { //RR
            return left_rotate(cur_node);
        } else { // RL
            cur_node->right = right_rotate(cur_node->right);
            return left_rotate(cur_node);
        }
    }

    return cur_node;
}

node_f find(node_t *cur_node, uint64_t key) {
    node_f result;
    result.node = NULL;
    result.d = 0;

    while (cur_node != NULL) {
        if (key < cur_node->key) {
            cur_node = cur_node->left;
        } else if (key > cur_node->key) {
            cur_node = cur_node->right;
        } else {
            result.node = cur_node;
            break;
        }
        result.d++;
    }

    return result;
}

// Pre-order printing.
void print_tree(FILE *ofp, node_t *cur_node) {
    if (cur_node != NULL) {
        fprintf(ofp, "(%lld, %lld) ", cur_node->key, cur_node->val);
        print_tree(ofp, cur_node->left);
        print_tree(ofp, cur_node->right);
    }
}

void delete_tree(node_t *root_node) {
    if (root_node == NULL) return;

    delete_tree(root_node->left);
    delete_tree(root_node->right);
    free(root_node);
}