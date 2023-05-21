#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct imp {
    char* val1;
    char* val2;
};

void print_in_file(FILE* fp, char* val1, const char* val2, const char* add, char c);
void final_step(FILE* f, FILE* fp, struct imp* temp, int ind);
