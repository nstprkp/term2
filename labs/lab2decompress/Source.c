#include "Header.h"

void print_in_file(FILE* fp, char* val1, char* val2, char* add, char c)
{
    if (add!=NULL) {
        
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
}

void final_step(FILE* f, FILE* fp, struct imp* temp, int ind)
{
    int t = 0;
    char buff[256];
    char c = ' ';
    while (!feof(f) && t == 0) {
        char st[6] = "/";
        fscanf(f, "%255s", buff);
        if (strcmp(buff, st) == 0) { t = 1; }
        if (t == 0) {
            if (c != NULL) {
                if (c == '\n') { fprintf(fp, "%c%c", c, c); }
                else {
                    if (c == ' ') {
                        fprintf(fp, "%c", c);
                    }
                }
            }
            char* add;
            add = calloc(256, sizeof(char));
            if (add != NULL) {
                add = strcpy(add, buff);
            }
            
            c = ' ';
            c = fgetc(f);

            char sep[16] = "[](),*.;:!?\" ";
            char* istr;
            istr = (char*)calloc(256, sizeof(char));
            char* saveptr = NULL;
            istr = strtok(buff, sep);
            
            if (strlen(buff) != 0) {
                istr = (char*)realloc(istr, (strlen(buff)+1)*sizeof(char));
            }
            int i = 0;
            int z = 0;
            if (temp != NULL && istr != NULL) {
                while (i < ind && z == 0) {
                    if (strcmp(temp[i].val1, istr) == 0) {

                        print_in_file(fp, temp[i].val2, temp[i].val1, add, c);
                        z++;
                    }
                    if (strcmp(istr, temp[i].val2) == 0) {
                        print_in_file(fp, temp[i].val1, temp[i].val2, add, c);
                        z++;
                    }
                    i++;
                }
                if (z == 0) {
                    fprintf(fp, "%s", add);
                }
            }
            free(add);
            free(istr);
        }
    }
}
