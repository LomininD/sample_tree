#ifndef TREE_FUNCS_H
#define TREE_FUNCS_H

#include "tree_properties.h"

enum tree_view
{
    preorder,
    postorder,
    inorder
};

err_t print_tree(const tree* tree, tree_view print_type);
err_t print_node(const node* node, tree_view print_type, md_t debug_mode);
void initialize_tree_log(md_t debug_mode);

#define print_data_if(COND, ...) do{                        \
    if (print_type == COND)                                 \
        printf_both(debug_mode, __VA_ARGS__);               \
}                                                           \
while(0)

#endif