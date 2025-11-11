#include <stdio.h>
#include "tree_properties.h"
#include "tree_funcs.h"
#include "tree_dump.h"

int main()
{
    md_t debug_mode = on;
    initialize_tree_log(debug_mode);
    
    // sample tree structure

    node node_6 = {6, NULL, NULL};
    node node_16 = {16, NULL, NULL};
    node node_13 = {13, NULL, NULL};
    node node_15 = {15, &node_13, &node_16};
    node node_7 = {7, &node_6, NULL};
    node node_3 = {3, NULL, NULL};
    node node_20 = {20, &node_15, NULL};
    node node_5 = {5, &node_3, &node_7};
    node root_node = {10, &node_5, &node_20};

    tree my_tree = {&root_node, 9, debug_mode};

    print_tree(&my_tree, inorder);

    process_tree_verification(&my_tree);

    print_tree_dump(&my_tree); 

    fclose(log_ptr);
    return 0;
}