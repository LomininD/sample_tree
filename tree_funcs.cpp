#include "tree_funcs.h"
#include <stdio.h>
#include <assert.h>


void initialize_tree_log(md_t debug_mode)
{
    log_ptr = fopen("tree_log.html", "w");
    printf_log_only(debug_mode, "<pre>\n");
    printf_log_only(debug_mode, "<h3> +++ TREE LOG +++ </h3>\n");
}

err_t print_tree(const node* node, tree_view print_type)
{
    assert(node != NULL);

    md_t debug_mode = node->debug_mode;

    printf_log_msg(debug_mode, "print_tree: began printing tree from node [%p]\n\n", node);

    err_t printed = print_node(node, print_type);

    if (printed != ok)
        return printed;

    printf_both(debug_mode, "\n");

    printf_log_msg(debug_mode, "\nprint_tree: done printing tree from node [%p]\n", node);

    return ok;
}

err_t print_node(const node* node, tree_view print_type)
{
    assert(node != NULL);

    md_t debug_mode = node->debug_mode;

    printf_log_msg(debug_mode, "(");

    print_data_if(preorder, "%d ", node->data);

    if (node->left != NULL)
        print_node(node->left, print_type);

    print_data_if(inorder, "%d ", node->data);
    
    if (node->right != NULL)
        print_node(node->right, print_type);

    print_data_if(postorder, "%d ", node->data);

    printf_log_msg(debug_mode, ")");


    return ok;
}