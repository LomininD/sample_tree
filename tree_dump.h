#ifndef TREE_DUMP_H
#define TREE_DUMP_H

#include "tree_properties.h"

const size_t file_name_size = 64;
const size_t sys_str_size = 200;

void generate_dump_image(const node* node);
void convert_to_image(char* code_file_name, char* image_file_name);
void fill_preamble(FILE* fp);
const node* list_nodes(FILE* fp, const node* current_node);


#define IMAGE_CODE_EXT "txt"
#define IMAGE_EXT "png"
#define IMAGE_CODE_PATH "dump_img/code/"
#define IMAGE_PATH "dump_img/"

#endif