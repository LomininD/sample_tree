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

    tree my_tree = {};
    tree ref_tree = {&root_node, 9, debug_mode, ok};

    tree_ctor(&my_tree, debug_mode);

    insert_tree(&my_tree, 10);
    insert_tree(&my_tree, 20);
    insert_tree(&my_tree, 5);
    insert_tree(&my_tree, 6);
    insert_tree(&my_tree, 15);
    insert_tree(&my_tree, 16);
    insert_tree(&my_tree, 13);
    insert_tree(&my_tree, 7);
    insert_tree(&my_tree, 3);


    print_tree(&my_tree, my_tree.root, inorder);
    print_tree(&ref_tree, ref_tree.root, inorder);

    print_tree_dump(&my_tree); 
    print_tree_dump(&ref_tree);

    delete_tree(&my_tree, my_tree.root->right);

    //process_tree_verification(&my_tree);

    print_tree_dump(&my_tree); 
    //print_tree_dump(&ref_tree);

    fclose(log_ptr);
    return 0;
}