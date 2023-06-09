#include "Header.h"

int check_st_in_stream(FILE* stream, char* buff, const char* st) {
    int t = 0;
    while (!feof(stream) && t == 0) {
        fscanf(stream, "%255s", buff);
        if (strcmp(buff, st) == 0) {
            t = 1;
        }
        for (int tt = 0; tt < 256; tt++) {
            buff[tt] = 0;
        }
    }
    return t;
}

void read_temp_entries(FILE* stream, char* buff, struct imp* temp, int* ind) {
    while (!feof(stream)) {
        fscanf(stream, "%255s", buff);
        temp[*ind].val2 = (char*)calloc(strlen(buff) + 1, sizeof(char));
        if (temp[*ind].val2 != NULL) {
            temp[*ind].val2 = strcpy(temp[*ind].val2, buff);
        }

        fscanf(stream, "%255s", buff);
        temp[*ind].val1 = (char*)calloc(strlen(buff) + 1, sizeof(char));
        if (temp[*ind].val1 != NULL) {
            temp[*ind].val1 = strcpy(temp[*ind].val1, buff);
        }
        (*ind)++;
        struct imp* ptr;
        ptr = (struct imp*)realloc(temp, (*ind + 1) * sizeof(struct imp));
        if (ptr != NULL) {
            temp = ptr;
        }
        ptr = NULL;
        free(ptr);
        ptr = NULL;
        for (int tt = 0; tt < 256; tt++) {
            buff[tt] = 0;
        }
    }
}

struct imp* read_temp_from_file(FILE** stream, char* buff, const char* st, int* ind) {
    struct imp* temp;
    temp = (struct imp*)malloc(1 * sizeof(struct imp));
    *stream = fopen("C:\\Users\\Настя\\source\\repos\\labb2\\labb2\\output.txt", "r");
    if (*stream != NULL) {
        int t = 0;
        t = check_st_in_stream(*stream, buff, st);
        if (t == 1) {
            read_temp_entries(*stream, buff, temp, ind);
        }
    } else {
        free(temp);
        return NULL;
    }
    return temp;
}

void free_temp(struct imp* temp, int ind) {
    for (int i = 0; i < ind; i++) {
        free(temp[i].val1);
        free(temp[i].val2);
    }
    free(temp);
}

int main() {
    FILE* stream;
    FILE* fp;
    FILE* f;
    char buff[256];
    char st[6] = "/";

    struct imp* temp;
    int ind = 0;
    temp = read_temp_from_file(&stream, buff, st, &ind);
    if (temp == NULL) {
        printf("File not found!\n");
        return 0;
    }
    fclose(stream);

    f = fopen("C:\\Users\\Настя\\source\\repos\\labb2\\labb2\\output.txt", "r");
    fp = fopen("out.txt", "w");

    if (f != NULL) {
        final_step(f, fp, temp, ind);
    } 
    if (f!=NULL) {fclose(f);}
    if (fp!=NULL) {fclose(fp);}
    free_temp(temp, ind);
    printf("check your result!\n");
    return 0;
}
