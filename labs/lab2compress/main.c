#include "Header.h"

int main()
{
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
    int n=0;
    int a = 0;
    char buff[256];
    stream = fopen("input.txt", "r");
    if (stream != NULL) {
        while (!feof(stream)) {
            fscanf(stream, "%255s", buff);

            char sep[16] = ",.;*:!?()[]\" ";
            char* istr;
            istr = calloc(256, sizeof(char));
            char* saveptr = NULL;
            istr = strtok(buff, sep);

            if (st1 != NULL) {
                push(st1, istr, n, a);
                n++;
            }
            istr = NULL;
            free(istr);
            for (int tt = 0; tt < 256; tt++) {
                buff[tt] = 0;
            }
        }
    }
    else {
        printf("\nFile not found.\n");
        free(st1); free(st2);
        return 0;
    }
    fclose(stream);

    struct words* word;
    word = (struct words*)calloc(1, sizeof(struct words));
    int kol = 0;

    if (st1 != NULL) {
        int t = st1[0].pointer;
        st1[0].pointer = t;
    }

    if (st2 != NULL && st1 != NULL) {
        while (st1[0].pointer > 0 || st2[0].pointer > 0) {
            int cnt;

            if (st1[0].pointer >= 0) {
                if (st1 != NULL) {
                    st1[0].pointer--;
                }

                char* onTop;
                onTop = top(st1);
                st2[0].pointer = 0;
                cnt = counting(st1, st2, onTop,n,a);

                if (word != NULL) {
                    make_struct(word, onTop, cnt, kol);
                    kol++;
                    struct words* ptr;
                    ptr = (struct words*)realloc(word, (kol + 1) * sizeof(struct words));
                    if (ptr != NULL) {
                        word = ptr;
                    }
                    ptr = NULL;
                    free(ptr);
                    ptr = NULL;
                }
                onTop = NULL;
                free(onTop);
                onTop = NULL;
                a++;
            }
            else {
                if (st2[0].pointer >= 0) {
                    if (st2[0].value != NULL) {
                        if (st2 != NULL) {
                            st2[0].pointer--;
                        }
                        char* onTop2;
                        onTop2 = top(st2);
                        st1[0].pointer = 0;
                        cnt = counting(st2, st1, onTop2, n,a);

                        if (word != NULL) {
                            make_struct(word, onTop2, cnt, kol);
                            kol++;
                            struct words* ptr;
                            ptr = (struct words*)realloc(word, (kol + 1) * sizeof(struct words));
                            if (ptr != NULL) {
                                word = ptr;
                            }
                            ptr = NULL;
                            free(ptr);
                            ptr = NULL;
                        }
                        onTop2 = NULL;
                        free(onTop2);
                        onTop2 = NULL;
                    }
                }
            }
        }
    }

    free_memory(st1, st2, n);

    qsort(word, kol, sizeof(struct words), comp_by_all);

    for (int i = 0; i < kol; i++) {
        word[i].met = 0;
    }
    struct imp* temp;
    temp = (struct imp*)malloc(1 * sizeof(struct imp));

    int ind = 0;
    int s = 0, l = kol - 1;
    if (word != NULL) {
        while (s != l) {
            if (word[l].len > word[s].len && word[l].num > word[s].num && word[l].met == 0 && word[s].met == 0) {
                temp[ind].val1 = (char*)calloc(word[l].len + 1, sizeof(char));
                strcpy(temp[ind].val1, word[l].val);

                temp[ind].val2 = (char*)calloc(word[s].len + 1, sizeof(char));
                strcpy(temp[ind].val2, word[s].val);

                int free_memory = abs((word[l].len * word[l].num) - (word[s].len * word[s].num));
                int need_memory = (word[l].len + word[s].len + 5);

                if (free_memory <= need_memory) {
                    l--;
                    continue;
                }

                ind++;
                struct imp* ptr;
                ptr = (struct imp*)realloc(temp, (ind + 1) * sizeof(struct imp));
                if (ptr != NULL) {
                    temp = ptr;
                }
                s++;
                ptr = NULL;
                free(ptr);
                ptr = NULL;
            }
            l--;
        }
    }


    f = fopen("input.txt", "r");
    fp = fopen("output.txt", "w");

    if (f != NULL) {
        final_step(f, fp, temp, ind);
        fclose(f);
    }
    else {
        return 0;
        fclose(f);
    }
    fprintf(fp, "\n/\n");
    for (int i = 0; i < ind; i++) {
        fprintf(fp, "%s ", temp[i].val1);
        fprintf(fp, "%s ", temp[i].val2);
    }
    fclose(fp);
    free(word);
    word = NULL;
    free(temp);
    temp = NULL;
    printf("check your result!\n");
    return 0;
}
