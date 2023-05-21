#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct stack {
    char** value;
    int pointer;
};

struct words {
    char* val;
    int num;
    int len;
    int met;
};

struct imp {
    char* val1;
    char* val2;
};

void push(struct stack* st, char* val, int n, int t);
void pop(struct stack* st);
char* top(struct stack* st);
int counting(struct stack* st1, struct stack* st2, char* onTop, int n, int t);
void make_struct(struct words* word, char* onTop, int cnt, int kol);
int comp_by_all(const void* typ1, const void* typ2);
void free_memory(struct stack* st1, struct stack* st2, int n);
void print_in_file(FILE* fp, char* val1, char* val2, char* add, char c);
void final_step(FILE* f, FILE* fp, struct imp* temp, int ind);
