#include <stdio.h>
#include "tree_properties.h"
#include "tree_funcs.h"
#include "tree_dump.h"

int main()
{
    md_t debug_mode = off;
    initialize_tree_log(debug_mode);
    
    // sample tree structure

    node node_6 = {6, NULL, NULL, debug_mode};
    node node_16 = {16, NULL, NULL, debug_mode};
    node node_13 = {13, NULL, NULL, debug_mode};
    node node_15 = {15, &node_13, &node_16, debug_mode};
    node node_7 = {7, &node_6, NULL, debug_mode};
    node node_3 = {3, NULL, NULL, debug_mode};
    node node_20 = {20, &node_15, NULL, debug_mode};
    node node_5 = {5, &node_3, &node_7, debug_mode};
    node root_node = {10, &node_5, &node_20, debug_mode};

    print_tree(&root_node, inorder);

    generate_dump_image(&root_node);

    fclose(log_ptr);
    return 0;
}