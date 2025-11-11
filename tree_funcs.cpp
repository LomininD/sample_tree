#include "tree_funcs.h"
#include <stdio.h>
#include <assert.h>


void initialize_tree_log(md_t debug_mode)
{
    log_ptr = fopen("tree_log.html", "w");
    printf_log_only(debug_mode, "<pre>\n");
    printf_log_only(debug_mode, "<h3> +++ TREE LOG +++ </h3>\n");
}

err_t print_tree(const tree* tree, tree_view print_type)
{
    assert(tree != NULL);

    md_t debug_mode = tree->debug_mode;

    printf_log_msg(debug_mode, "print_tree: began printing tree from root node [%p]\n\n", tree->root);

    err_t printed = print_node(tree->root, print_type, debug_mode);

    if (printed != ok)
        return printed;

    printf_both(debug_mode, "\n");

    printf_log_msg(debug_mode, "\nprint_tree: done printing tree\n");

    return ok;
}

err_t print_node(const node* node, tree_view print_type, md_t debug_mode)
{
    assert(node != NULL);

    printf_log_msg(debug_mode, "(");

    print_data_if(preorder, "%d ", node->data);

    if (node->left != NULL)
        print_node(node->left, print_type, debug_mode);

    print_data_if(inorder, "%d ", node->data);
    
    if (node->right != NULL)
        print_node(node->right, print_type, debug_mode);

    print_data_if(postorder, "%d ", node->data);

    printf_log_msg(debug_mode, ")");

    return ok;
}