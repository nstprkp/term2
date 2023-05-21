#include "treeAPI.h"

tree_node* get_free_node(char* data, tree_node* parent)
{
    tree_node* new_node = (tree_node*)malloc(sizeof(tree_node));
    new_node->data = (char*)calloc(strlen(data)+1, sizeof(char));
    if ( strcmp(data, ".\n") != 0 ) {
        strcpy(new_node->data, data);
    }
    else {
        new_node->data = NULL;
    }
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert(tree_node** head, char* value, int check)
{
    tree_node* tmp = NULL;
    if (*head == NULL) {
        *head = get_free_node(value, tmp);
    }

    tmp = *head;
    int mas[check];
    int t = check;
    int i = 0;
    while (t != 1) {
        mas[i] = t % 2;
        t = t / 2;
        i++;
    }
    i--;
    while (tmp && i >= 0 && check != 1) {
        if (mas[i] != 0) {
            if (tmp->right) {
                tmp = tmp->right;
                i--;
                continue;
            } else {
                tmp->right = get_free_node(value, tmp);
                return;
            }
        }
        else {
            if (tmp->left) {
                tmp = tmp->left;
                i--;
                continue;
            } else {
                tmp->left = get_free_node(value, tmp);
                return;
            }
        }
    }
}

char* get_elem(tree_node *head, int check)
{
    tree_node* tmp = NULL;
    tmp = head;
    int mas[check];
    int t = check;
    int i = 0;
    if (check == 1) {
        return tmp->data;
    }
    while (t != 1) {
        mas[i] = t % 2;
        t = t / 2;
        i++;
    }
    i--;
    char str[256] = "asdfghjkl";
    while (tmp && check != 1) {
        if (mas[i] != 0) {
            if (i>0) {
                tmp = tmp->right;
                i--;
                continue;
            } else {
                //  if (tmp->right->right == NULL) {ans++;}
                return tmp->right->data;
            }
        }
        else {
            if (i>0) {
                tmp = tmp->left;
                i--;
                continue;
            } else {
                //  if (tmp->left->left == NULL) {ans++;}
                return tmp->left->data;
            }
        }
    }
    return head->data;
}



int get_ans(tree_node *head, int check)
{
    int ans = 0;
    tree_node* tmp = NULL;
    tmp = head;
    int mas[check];
    int t = check;
    int i = 0;
    while (t != 1) {
        mas[i] = t % 2;
        t = t / 2;
        i++;
    }
    i--;
    while (tmp && check != 1) {
        if (mas[i] != 0) {
            if (i>0) {
                tmp = tmp->right;
                i--;
                continue;
            } else {
                if (tmp->right->right->data == NULL || tmp->right->right == NULL) {ans++;}
                return ans;
            }
        }
        else {
            if (i>0) {
                tmp = tmp->left;
                i--;
                continue;
            } else {
                if (tmp->left->left->data == NULL || tmp->left->left == NULL) {ans++;}
                return ans;
            }
        }
    }
    return ans;
}

void new_insert(tree_node** head, char* value, int check)
{
    tree_node* tmp = NULL;
    if (*head == NULL) {
        *head = get_free_node(value, tmp);
    }

    tmp = *head;
    int mas[check];
    int t = check;
    int i = 0;
    while (t != 1) {
        mas[i] = t % 2;
        t = t / 2;
        i++;
    }
    i--;
    while (tmp && i >= 0 && check != 1) {
        if (mas[i] != 0) {
            if (i>0) {
                tmp = tmp->right;
                i--;
                continue;
            } else {
                if (tmp->right != NULL) {
                    tmp->right->data = NULL;
                }
                tmp->right->data = (char*)malloc(strlen(value) + 1);
                strcpy(tmp->right->data, value);
                return;
            }
        }
        else {
            if (i>0) {
                tmp = tmp->left;
                i--;
                continue;
            } else {
                if (tmp->left != NULL) {
                    tmp->left->data = NULL;
                }
                tmp->left->data = (char*) malloc(strlen(value) + 1);
                strcpy(tmp->left->data, value);
                return;
            }
        }
    }
}

void print_tree(tree_node *root, const char *dir, int level) {
    if (root) {
        printf("lvl %d %s = %s\n", level, dir, root->data);
        print_tree(root->left, "left", level+1);
        print_tree(root->right, "right", level+1);
    }
}

void free_tree(tree_node *tree)
{
    if (tree != NULL) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}
