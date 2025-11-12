#include "tree_funcs.h"
#include <stdio.h>
#include <assert.h>


static node* create_node(md_t debug_mode);
static bool cmp(tree_el_t value_1, tree_el_t value_2);
static err_t delete_node(tree* tree, node* node);


void initialize_tree_log(md_t debug_mode)
{
    log_ptr = fopen("tree_log.html", "w");
    printf_log_only(debug_mode, "<pre>\n");
    printf_log_only(debug_mode, "<h3> +++ TREE LOG +++ </h3>\n");
}


err_t tree_ctor(tree* tree, md_t debug_mode)
{
    if (tree == NULL)
    {
        printf_err(debug_mode, "[from tree_ctor] -> tree not found\n");
        return error;
    }

    printf_log_msg(debug_mode, "tree_ctor: began initialising tree [%p]", tree);

    tree->debug_mode = debug_mode;

    VERIFY_TREE(error);

    printf_log_msg(debug_mode, "tree_ctor: finished initialising tree [%p]", tree);

    return ok;
}


err_t insert_tree(tree* tree, tree_el_t value)
{
    VERIFY_TREE(error);

    md_t debug_mode = tree->debug_mode;

    printf_log_msg(debug_mode, "insert_tree: began inserting %d\n", value);

    node** current_node = &(tree->root);

    while(*current_node != NULL)
    {
        printf_log_msg(debug_mode, "insert_tree: current node is [%p]\n", *current_node);

        if (cmp(value, (*current_node)->data))
        {
            printf_log_msg(debug_mode, "insert_tree: %d is greater than %d, right subtree of node [%p] chosen\n", \
                                                            value, (*current_node)->data, *current_node);
            current_node = &(*current_node)->right;
        }
        else
        {
            printf_log_msg(debug_mode, "insert_tree: %d is greater than %d, left subtree of node [%p] chosen\n", \
                                                           (*current_node)->data, value, *current_node);
            current_node = &(*current_node)->left;
        }
    }

    node* new_node = create_node(debug_mode);

    if (new_node == NULL)
    {
        printf_err(debug_mode, "[from insert_tree] -> could not create new node for inserted element\n");
        tree->err_stat = error;
        return error;
    }

    new_node->data = value;
    *current_node = new_node;
    tree->size++;

    VERIFY_TREE(error);

    printf_log_msg(debug_mode, "insert_tree: finished inserting %d\n", value);

    DISPLAY_TREE();

    return ok;
}


bool cmp(tree_el_t value_1, tree_el_t value_2)
{
    if (value_1 > value_2)
        return true;
    else
        return false;
}


node* create_node(md_t debug_mode)
{
    printf_log_msg(debug_mode, "create_node: began creating node\n");

    node* new_node = (node*) calloc(1, sizeof(node));

    printf_log_msg(debug_mode, "create_node: done creating node [%p]\n", new_node);

    return new_node;
}

err_t delete_tree(tree* tree, node* anchor_node)
{
    VERIFY_TREE(error);

    md_t debug_mode = tree->debug_mode;

    printf_log_msg(debug_mode, "delete_tree: began deleting tree from node [%p]\n", anchor_node);

    node** current_node = &tree->root;
    bool found = false;

    if (*current_node == NULL)
    {
        printf_err(debug_mode, "[from delete_tree] -> no elements in tree\n");
        tree->err_stat = error;
        return error;
    }

    if (*current_node == anchor_node)
    {
        delete_node(tree, anchor_node);
        *current_node = NULL;
        found = true;
    }

    while(*current_node != NULL && !found)
    {
        if ((*current_node)->left == anchor_node)
        {
            delete_node(tree, anchor_node);
            (*current_node)->left = NULL;
            found = true;
        }
        else if ((*current_node)->right == anchor_node)
        {
            delete_node(tree, anchor_node);
            (*current_node)->right = NULL;
            found = true;
        }
        else
        {
            if (cmp(anchor_node->data, (*current_node)->data))
                current_node = &(*current_node)->right;
            else
                current_node = &(*current_node)->left;
        }
    }

    if (found)
    {
        printf_log_msg(debug_mode, "delete_tree: finished deleting node\n");
        return ok;
    }
    else
    {
        printf_err(debug_mode, "[from delete_tree] -> node not found\n");
        tree->err_stat = error;
        return error;
    }

    VERIFY_TREE(error);

    DISPLAY_TREE();
}


err_t delete_node(tree* tree, node* node)
{
    //printf("deleting [%p]\n", node);

    if (node == NULL)
        return ok;
    
    delete_node(tree, node->left);
    delete_node(tree, node->right);

    free(node);
    tree->size--;

    //printf("done deleting [%p]\n", node);

    return ok;
}


err_t print_tree(const tree* tree, const node* root, tree_view print_type)
{
    assert(root != NULL);
    assert(tree != NULL);

    VERIFY_TREE(error);

    md_t debug_mode = tree->debug_mode;

    printf_log_msg(debug_mode, "print_tree: began printing tree from node [%p]\n\n", root);

    err_t printed = print_node(root, print_type, debug_mode);

    if (printed != ok)
    {
        return printed;
    }

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