#include "Header.h"

char* getStr(char *s, int k)
{
    char c;
    int chr;
    int i=0;
    while(--k > 0 && (chr = getchar())!=EOF && c != '\n') {
        c = (char)chr;
        s[i++] = c;
    }
    s[i] = '\0';
    return s;
}
