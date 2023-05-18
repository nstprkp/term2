#include "Header.h"

int main()
{
    FILE* stream;
    FILE* fp;
    FILE* f;
    char buff[256];
    char st[6] = "/";

    struct imp* temp;
    temp = (struct imp*)malloc(1 * sizeof(struct imp));
    int ind = 0;
    stream = fopen("C:\\Users\\Настя\\source\\repos\\labb2\\labb2\\output.txt", "r");
    if (stream != NULL) {
        int t = 0;
        while (!feof(stream) && t==0) {
            fscanf(stream, "%255s", buff);
            // printf("%s\n", buff);
            if (strcmp(buff, st) == 0) {
                t = 1;
            }
            for (int tt = 0; tt < 256; tt++) {
                buff[tt] = 0;
            }
        }
        if (t == 1) {
            while (!feof(stream)) {
                fscanf(stream, "%255s", buff);
                temp[ind].val2 = (char*)calloc(strlen(buff)+1, sizeof(char));
                if (temp[ind].val2 != NULL) {
                    temp[ind].val2 = strcpy(temp[ind].val2, buff);
                }

                fscanf(stream, "%255s", buff);
                temp[ind].val1 = (char*)calloc(strlen(buff)+1, sizeof(char));
                if (temp[ind].val1 != NULL) {
                    temp[ind].val1 = strcpy(temp[ind].val1, buff);
                }
                ind++;
                struct imp* ptr;
                ptr = (struct imp*)realloc(temp, (ind + 1) * sizeof(struct imp));
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
    }
    else {
        printf("File not found!\n");
        return 0;
    }
    fclose(stream);

    f = fopen("C:\\Users\\Настя\\source\\repos\\labb2\\labb2\\output.txt", "r");
    fp = fopen("out.txt", "w");

    if (f != NULL) {
        final_step(f, fp, temp, ind);
    }
    else { return 0; }
    fclose(f);
    fclose(fp);
    free(temp);
    temp = NULL;
    printf("check yor result!\n");
    return 0;
}