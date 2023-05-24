#include "Header.h"

void process_input_file(struct stack* st1, FILE* stream, int* n, int* a) {
    char buff[256];
    while (!feof(stream)) {
        fscanf(stream, "%255s", buff);

        char sep[16] = ",.;*:!?()[]\" ";
        const char* istr;
        istr = strtok(buff, sep);

        if (st1 != NULL) {
            push(st1, istr, *n, *a);
            (*n)++;
        }
        istr = NULL;
        free(istr);
        for (int tt = 0; tt < 256; tt++) {
            buff[tt] = 0;
        }
    }
}

void process_words(struct stack* st1, struct stack* st2, struct words** word, int* kol, int* n, int* a) {
    while (st1[0].pointer > 0 || st2[0].pointer > 0) {
        int cnt;

        if (st1[0].pointer >= 0) {
            process_st1(st1, st2, word, kol, n, a, &cnt);
        } else {
            process_st2(st1, st2, word, kol, n, a, &cnt);
        }
    }
}

void process_st1(struct stack* st1, struct stack* st2, struct words** word, int* kol, int* n, int* a, int* cnt) {
    if (st1 != NULL) {
        st1[0].pointer--;
    }

    char* onTop;
    onTop = top(st1);
    st2[0].pointer = 0;
    *cnt = counting(st1, st2, onTop, *n, *a);

    if (*word != NULL) {
        make_struct(*word, onTop, *cnt, *kol);
        (*kol)++;
        struct words* ptr;
        ptr = (struct words*)realloc(*word, (*kol + 1) * sizeof(struct words));
        if (ptr != NULL) {
            *word = ptr;
        }
        ptr = NULL;
        free(ptr);
        ptr = NULL;
    }
    onTop = NULL;
    free(onTop);
    onTop = NULL;
    (*a)++;
}

void process_st2(struct stack* st1, struct stack* st2, struct words** word, int* kol, int* n, int* a, int* cnt) {
    if (st2 != NULL) {
        st2[0].pointer--;
    }

    char* onTop2;
    onTop2 = top(st2);
    st1[0].pointer = 0;
    *cnt = counting(st2, st1, onTop2, *n, *a);

    if (*word != NULL) {
        make_struct(*word, onTop2, *cnt, *kol);
        (*kol)++;
        struct words* ptr;
        ptr = (struct words*)realloc(*word, (*kol + 1) * sizeof(struct words));
        if (ptr != NULL) {
            *word = ptr;
        }
        ptr = NULL;
        free(ptr);
        ptr = NULL;
    }
    onTop2 = NULL;
    free(onTop2);
    onTop2 = NULL;
}


void process_word_struct(struct words* word, struct imp** temp, int* ind, int kol) {
    int s = 0;
    int l = kol - 1;
    if (word != NULL) {
        while (s != l) {
            if (word[l].len > word[s].len && word[l].num > word[s].num && word[l].met == 0 && word[s].met == 0) {
                process_matching_words(&word[l], &word[s], temp, ind);
            }
            l--;
        }
    }
}

void process_matching_words(struct words* word1, struct words* word2, struct imp** temp, int* ind) {
    (*temp)[*ind].val1 = (char*)calloc(word1->len + 1, sizeof(char));
    strcpy((*temp)[*ind].val1, word1->val);

    (*temp)[*ind].val2 = (char*)calloc(word2->len + 1, sizeof(char));
    strcpy((*temp)[*ind].val2, word2->val);

    int free_memory = abs((word1->len * word1->num) - (word2->len * word2->num));
    int need_memory = (word1->len + word2->len + 5);

    if (free_memory <= need_memory) {
        return;
    }

    (*ind)++;
    struct imp* ptr;
    ptr = (struct imp*)realloc(*temp, (*ind + 1) * sizeof(struct imp));
    if (ptr != NULL) {
        *temp = ptr;
    }
    ptr = NULL;
    free(ptr);
    ptr = NULL;
}


void process_output_file(FILE* f, FILE* fp, struct imp* temp, int ind) {
    if (f != NULL) {
        final_step(f, fp, temp, ind);
    } else {
        return;
    }
    fprintf(fp, "\n/\n");
    for (int i = 0; i < ind; i++) {
        fprintf(fp, "%s ", temp[i].val1);
        fprintf(fp, "%s ", temp[i].val2);
    }
}

int main() {
    FILE* stream;
    FILE* fp;
    FILE* f;
    struct stack* st1;
    struct stack* st2;
    st1 = (struct stack*)calloc(1, sizeof(struct stack));
    st2 = (struct stack*)calloc(1, sizeof(struct stack));

    if (st1 != NULL) {
        st1[0].pointer = 0;
        st1[0].value = (char**)calloc(1, sizeof(char*));
    }
    if (st2 != NULL) {
        st2[0].pointer = 0;
        st2[0].value = (char**)calloc(1, sizeof(char*));
    }

    int n = 0;
    int a = 0;

    stream = fopen("input.txt", "r");
    if (stream == NULL) {
        printf("\nFile not found.\n");
        free(st1);
        free(st2);
        return 0;
    }

    process_input_file(st1, stream, &n, &a);
    fclose(stream);

    struct words* word;
    word = (struct words*)calloc(1, sizeof(struct words));
    int kol = 0;

    if (st1 != NULL) {
        int t = st1[0].pointer;
        st1[0].pointer = t;
    }

    if (st2 != NULL && st1 != NULL) {
        process_words(st1, st2, &word, &kol, &n, &a);
    }

    free_memory(st1, st2, n);

    qsort(word, kol, sizeof(struct words), comp_by_all);

    for (int i = 0; i < kol; i++) {
        word[i].met = 0;
    }
    struct imp* temp;
    temp = (struct imp*)malloc(1 * sizeof(struct imp));

    int ind = 0;
    process_word_struct(word, &temp, &ind, kol);

    f = fopen("input.txt", "r");
    fp = fopen("output.txt", "w");

    process_output_file(f, fp, temp, ind);

    fclose(f);
    fclose(fp);
    free(word);
    word = NULL;
    free(temp);
    temp = NULL;
    printf("check your result!\n");
    return 0;
}
