#ifndef TREE_PROPERTIES_H
#define TREE_PROPERTIES_H

#include "debug.h"

typedef int tree_el_t;

const tree_el_t poison_value = 0xbadf00d;

struct node
{
    tree_el_t data;
    node* left;
    node* right;
};

struct tree
{
    node* root;
    size_t size;
    md_t debug_mode;
    err_t err_stat;
};

#endif