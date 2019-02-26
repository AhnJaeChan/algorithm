//
// Created by 안재찬 on 20/11/2018.
//

#include "rbtree.h"

node_t *init_node(uint64_t key, uint64_t val) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));

    new_node->key = key;
    new_node->val = val;

    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    // Initial color = RED
    new_node->color = RED;

    return new_node;
}

void left_rotate(node_t *node) {
    // 1. Take nodes needed for rotation
    node_t *right_child = node->right;
    node_t *mid_sub_tree = right_child->left;

    // 2. Left rotate the (sub)tree
    right_child->left = node;
    node->right = mid_sub_tree;

    // 3. Change the parents of the rotated nodes
    right_child->parent = node->parent;

    if (right_child->parent != NULL) {
        if (node == right_child->parent->right) {
            right_child->parent->right = right_child;
        } else {
            right_child->parent->left = right_child;
        }
    }

    node->parent = right_child;

    if (mid_sub_tree != NULL) {
        mid_sub_tree->parent = node;
    }
}

void right_rotate(node_t *node) {
    // 1. Take nodes needed for rotation
    node_t *left_child = node->left;
    node_t *mid_sub_tree = left_child->right;

    // 2. Right rotate the (sub)tree
    left_child->right = node;
    node->left = mid_sub_tree;

    // 3. Change the parents of the rotated nodes
    left_child->parent = node->parent;

    if (left_child->parent != NULL) {
        if (node == left_child->parent->left) {
            left_child->parent->left = left_child;
        } else {
            left_child->parent->right = left_child;
        }
    }

    node->parent = left_child;

    if (mid_sub_tree != NULL) {
        mid_sub_tree->parent = node;
    }
}

node_t *bst_insert(node_t *root_node, node_t *new_node) {
    if (root_node == NULL) {
        return new_node;
    }

    if (root_node->key > new_node->key) {
        root_node->left = bst_insert(root_node->left, new_node);
        root_node->left->parent = root_node;
    } else if (root_node->key < new_node->key) {
        root_node->right = bst_insert(root_node->right, new_node);
        root_node->right->parent = root_node;
    }

    return root_node;
}

node_t *fix_tree(node_t *root_node, node_t *cur_node) {
    if (cur_node == root_node) {
        cur_node->color = BLACK;
        return root_node;
    }

    node_t *parent_node = cur_node->parent;

    if (parent_node->color == BLACK) {
        return root_node;
    }

    node_t *grand_parent_node = parent_node->parent;
    node_t *uncle_node = parent_node == grand_parent_node->left ? grand_parent_node->right : grand_parent_node->left;

    if (uncle_node != NULL && uncle_node->color == RED) { // Uncle nodes' color is RED
        // Change color of parent and uncle node to BLACK, grand parent to RED
        // Call recursively with cur_node as grand parent.
        grand_parent_node->color = RED;
        parent_node->color = BLACK;
        uncle_node->color = BLACK;

        return fix_tree(root_node, grand_parent_node);
    } else { // Uncle nodes' color is BLACK
        // 4 cases(LL, LR, RR, RL) exists. Similar to AVL tree but needs rotation + coloring (2 steps).
        if (parent_node == grand_parent_node->left) { // If parent node is left child of grand parent.
            if (cur_node == parent_node->left) { // If current node is left child of parent (Left Left case)
                grand_parent_node->color = RED;
                parent_node->color = BLACK;
                right_rotate(grand_parent_node);

                return grand_parent_node == root_node ? parent_node : root_node; // Checks if the root changes
            } else { // If current node is right child of parent (Left Right case)
                left_rotate(parent_node);

                return fix_tree(root_node, parent_node);
            }
        } else { // If parent node is right child of grand parent.
            if (cur_node == parent_node->right) { // If current node is right child of parent (Right Right case)
                grand_parent_node->color = RED;
                parent_node->color = BLACK;
                left_rotate(grand_parent_node);

                return grand_parent_node == root_node ? parent_node : root_node; // Checks if the root changes
            } else { // If current node is left child of parent (Right Left case)
                right_rotate(parent_node);

                return fix_tree(root_node, parent_node);
            }
        }
    }
}

node_t *insert(node_t *root, uint64_t key, uint64_t val) {
    node_t *new_node = init_node(key, val);

    root = bst_insert(root, new_node);

    return fix_tree(root, new_node);
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
