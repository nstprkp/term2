#include "Header.h"

char* get_str(char* s, int k)
{
    char c;
    int ch;
    int i = 0;
    while (--k > 0) {
        ch = getchar();
        if (ch == EOF || ch == 13) {
            break;
        }
        c = (char)ch;
        s[i++] = c;
    }
    s[i] = '\0';
    return s;
}
