#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tree_node {
    char* data;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;

tree_node* get_free_node(char* data, tree_node* parent);
void insert(tree_node** head, char* value, int check);
char* get_elem(tree_node *head, int check);
int get_ans(tree_node *head, int check);
void new_insert(tree_node** head, char* value, int check);
void print_tree(tree_node *root, const char *dir, int level);
void free_tree(tree_node *tree);