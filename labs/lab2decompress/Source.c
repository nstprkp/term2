#include "Header.h"

void print_in_file(FILE* fp, char* val1, const char* val2, const char* add)
{
    if (add!=NULL) {
        
        if (strcmp(val2, add) != 0) {
            int z = 0;
            while (add[z] != val2[0]) {
                fprintf(fp, "%c", add[z]);
                z++;
            }
            fprintf(fp, "%s", val1);
            z = z + (int)strlen(val2);
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
        char st[2] = "/";
        fscanf(f, "%255s", buff);
        
        if (strcmp(buff, st) == 0) {
            t = 1;
        }
        
        if (t == 0) {
            if (c != '\0') {
                if (c == '\n') {
                    fprintf(fp, "%c%c", c, c);
                } else if (c == ' ') {
                    fprintf(fp, "%c", c);
                }
            }
            
            char* add = calloc(256, sizeof(char));
            if (add != NULL) {
                strcpy(add, buff);
            }
            
            c = ' ';
            int ch;
            ch = fgetc(f);
            c = (char)ch;
            
            char sep[16] = "[](),*.;:!?\"";
            const char* istr;
            if (buff != NULL) {
                istr = strtok(buff, sep);
            }
            
            int i = 0;
            int z = 0;
            
            if (temp != NULL && istr != NULL) {
                while (i < ind && z == 0) {
                    if (strcmp(temp[i].val1, istr) == 0) {
                        print_in_file(fp, temp[i].val2, temp[i].val1, add);
                        z++;
                    } else if (strcmp(istr, temp[i].val2) == 0) {
                        print_in_file(fp, temp[i].val1, temp[i].val2, add);
                        z++;
                    }
                    i++;
                }
                
                if (z == 0) {
                    fprintf(fp, "%s", add);
                }
            }
            
            free(add);
        }
    }
}
