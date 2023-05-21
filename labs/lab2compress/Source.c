#include "Header.h"

void push(struct stack* st, const char* val, int n, int t)
{
    if (val == NULL) {
        return;
    }
    st->value[st[0].pointer] = NULL;
    st[0].value[st[0].pointer] = (char*)calloc(strlen(val) + 1, sizeof(char));
    if (st != NULL && st[0].value[st[0].pointer] != NULL) {
        strcpy(st[0].value[st[0].pointer], val);
        char** ptr;
        st[0].pointer++;
        if (st[0].pointer >= n || t == 0) {
            ptr = (char**)realloc(st[0].value, (st[0].pointer + 1) * sizeof(char*));
            if (ptr != NULL) {
                st[0].value = ptr;
            }
        }
        ptr = NULL;
        free(ptr);
    }
}

void pop(struct stack* st) {
    if (st[0].pointer == 0) {
        exit(1);
    }
    st[0].pointer--;
}

char* top(const struct stack* st) {
    if (st[0].pointer == 0) {
        exit(1);
    }
    return st[0].value[st[0].pointer];
}

int counting(struct stack* st1, struct stack* st2, const char* onTop, int n, int t)
{
    int cnt = 1;
    pop(st1);
    while (st1[0].pointer >= 0) {
        if (strcmp(top(st1), onTop) == 0) { cnt++; }
        else {
            push(st2, top(st1), n, t);
        }
        pop(st1);
    }
    return cnt;
}

void make_struct(struct words* word, const char* onTop, int cnt, int kol)
{
    word[kol].val = (char*)calloc(strlen(onTop)+1, sizeof(char));
    if (word[kol].val != 0) {
        strcpy(word[kol].val, onTop);
    }
    word[kol].num = cnt;
    word[kol].len = (int)strlen(onTop);
}

int comp_by_all(const void* typ1, const void* typ2) {
    const struct words* p1 = (const struct words*)typ1;
    const struct words* p2 = (const struct words*)typ2;
    int cmp;
    cmp = p1->num - p2->num;
    if (cmp) return cmp;
    return p1->len - p2->len;
}

void free_memory(struct stack* st1, struct stack* st2, int n)
{

    for (int i = 0; i < n; i++) {
        st1[0].value[i] = NULL;
        free(st1[0].value[i]);
        st1[0].value[i] = NULL;
    }
    free(st1);
    st1 = NULL;
    int k = 0;
    if (st2 != NULL) {
        while (st2[0].value[k] != NULL) {
            st2[0].value[k] = NULL;
            free(st2[0].value[k]);
            st2[0].value[k] = NULL;
            k++;
        }
    }
    free(st2);
    st2 = NULL;
}

void print_in_file(FILE* fp, char* val1, const char* val2, const char* add, char c)
{
    if (add != NULL) {
        if (strcmp(val2, add) != 0) {
            int z = 0;
            while (add[z] != val2[0]) {
                fprintf(fp, "%c", add[z]);
                z++;
            }
            fprintf(fp, "%s", val1);
            z = z + strlen(val2);
            while (add[z] != '\n' && add[z] != '\0') {
                fprintf(fp, "%c", add[z]);
                z++;
            }
        }
        else {
            fprintf(fp, "%s", val1);
        }
    }
    

    if (c == '\n') { fprintf(fp, "%c", c); }
    else {
        if (c == ' ') {
            fprintf(fp, "%c", c);
        }
    }
}

void final_step(FILE* f, FILE* fp, struct imp* temp, int ind)
{
    char buff[256];
    while (!feof(f)) {
        fscanf(f, "%255s", buff);
        char* add;
        add = calloc(256, sizeof(char));
        if (add != NULL) {
            add = strcpy(add, buff);
        }
        char c = fgetc(f);

        char sep[16] = "[](),*.;:!?\" ";
        char* istr;
        istr = calloc(256, sizeof(char));
        istr = strtok(buff, sep);

        int i = 0;
        int t = 0;
        if (temp != NULL && istr != NULL) {
            while (i < ind && t == 0) {
                if (strcmp(temp[i].val1, istr) == 0) {

                    print_in_file(fp, temp[i].val2, temp[i].val1, add, c);
                    t++;
                }
                if (strcmp(istr, temp[i].val2) == 0) {
                    print_in_file(fp, temp[i].val1, temp[i].val2, add, c);
                    t++;
                }
                i++;
            }
            if (t == 0) {
                fprintf(fp, "%s", add);
                if (c == '\n') { fprintf(fp, "%c", c); }
                else {
                    if (c == ' ') {
                        fprintf(fp, "%c", c);
                    }
                }
            }
        }
        for (int tt = 0; tt < 256; tt++) {
            buff[tt] = 0;
        }
        istr = NULL;
        free(istr);
        istr = NULL;
        add = NULL;
        free(add);
        add = NULL;
    }
}
