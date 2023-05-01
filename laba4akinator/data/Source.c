#include "Header.h"

char* getStr(char *s, int k)
{
    int c, i=0;
    while(--k > 0 && (c = getchar())!=EOF && c != '\n')
        s[i++] = c;
    s[i] = '\0';
    return s;
}
