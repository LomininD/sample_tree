#include "tree_dump.h"
#include <stdio.h>
#include <assert.h>

static int hash(long long int ptr);


// make different number of args
void print_tree_dump(const tree* tree)
{
    assert(tree != NULL);


}


// generates tree graph and puts in html log file
void generate_dump_image(const tree* tree)
{
    assert(tree != NULL);

    static unsigned long long image_count = 0; // size_t?

    char code_file_name[file_name_size] = {};
    char image_file_name[file_name_size] = {};
    snprintf(code_file_name, file_name_size, IMAGE_CODE_PATH "%llu." IMAGE_CODE_EXT, image_count);
    snprintf(image_file_name, file_name_size, IMAGE_PATH "%llu." IMAGE_EXT, image_count);

    FILE* fp = fopen(code_file_name, "w");

    fprintf(fp, "digraph G\n");
    fprintf(fp, "{\n");

    fill_preamble(fp);

    fprintf(fp, "{\n");
    fprintf(fp, "edge[color = \"#45503B\", penwidth = 1]\n");
    list_nodes(fp, tree->root);
    fprintf(fp, "}\n\n");

    fprintf(fp, "}\n");

    fclose(fp);
    image_count++;

    convert_to_image(code_file_name, image_file_name);

    printf_log_only(tree->debug_mode, "\n\n <img src=\"%s\"> \n\n", image_file_name);
}


void convert_to_image(char* code_file_name, char* image_file_name)
{
    assert(code_file_name != NULL);
    assert(image_file_name != NULL);

    char sys_str[sys_str_size] = {};
    snprintf(sys_str, sys_str_size, "dot %s -T " IMAGE_EXT " -o %s", code_file_name, image_file_name); 

    //puts(sys_str);

    system(sys_str);
}


void fill_preamble(FILE* fp)
{
    assert(fp != NULL);

    // fprintf(fp, "rankdir = LR;\n");
    fprintf(fp, "bgcolor = \"white\"\n");
    fprintf(fp, "node[shape = doubleoctagon, style = \"filled\", fillcolor = \"red\", fontcolor = \"white\"]\n");
}


const node* list_nodes(FILE* fp, const node* current_node)
{
    assert(fp);
    assert(current_node);

    fprintf(fp, "NODE_%p [label = <", current_node);
    fprintf(fp, "<TABLE BORDER=\"0\" CELLBORDER=\"1\">");

    fprintf(fp, "<TR>");
    fprintf(fp, "<TD COLSPAN=\"2\">");
    fprintf(fp, "ptr =<FONT color=\"#%x\"> %p </FONT>", hash((long long int) current_node), current_node);
    fprintf(fp, "</TD>");
    fprintf(fp, "</TR>");

    fprintf(fp, "<TR>");
    fprintf(fp, "<TD COLSPAN=\"2\">");
    fprintf(fp, "value = ");
    if (current_node->data == poison_value)
        fprintf(fp, "%x", current_node->data);
    else
        fprintf(fp, "%d", current_node->data);
    fprintf(fp, "</TD>");
    fprintf(fp, "</TR>");

    fprintf(fp, "<TR>");
    fprintf(fp, "<TD PORT=\"f0\">");
    fprintf(fp, "left =<FONT color=\"#%x\"> %p </FONT>", hash((long long int) current_node->left), current_node->left);
    fprintf(fp, "</TD>");
    fprintf(fp, "<TD PORT=\"f1\">");
    fprintf(fp, "right =<FONT color=\"#%x\"> %p </FONT>", hash((long long int) current_node->right), current_node->right);
    fprintf(fp, "</TD>");
    fprintf(fp, "</TR>");
    fprintf(fp, "</TABLE>>, shape = plain, style = filled, " \
                "fillcolor = \"#C0C0C0\", fontcolor = \"black\"]\n");
        
    if (current_node->left != NULL)
    {
        const node* next_node = list_nodes(fp, current_node->left);
        fprintf(fp, "NODE_%p:f0 -> NODE_%p\n", current_node, next_node);
    }

    if (current_node->right != NULL)
    {
        const node* next_node = list_nodes(fp, current_node->right);
        fprintf(fp, "NODE_%p:f1 -> NODE_%p\n", current_node, next_node);
    }

    return current_node;    
}


int hash(long long int ptr)
{
    int hashed = 0;

    if (ptr == 0)
    {
        return 16711680;
    }

    while (ptr != 0)
    {
        hashed += (7717 * (ptr % 10) % 1013 + 349) * 147867;
        ptr /= 10; 
    }

    hashed %= 16777215;

    return hashed;
}

