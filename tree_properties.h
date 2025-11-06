#ifndef TREE_PROPERTIES_H
#define TREE_PROPERTIES_H

#include "debug.h"

typedef int tree_el_t;

const tree_el_t poison_value = 0xbadf00d;

// tree struct?

struct node
{
    tree_el_t data;
    node* left;
    node* right;
    md_t debug_mode;
};

#endif