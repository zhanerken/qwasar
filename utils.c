#include "my_ls.h"

void *my_memset(void *b, int c, int len)
{
    unsigned char *p = b;

    while (len > 0)
    {
    *p = c;
    p++;
    len--;
    }

    return (b);
}

char *my_strcat(char *dest, const char *src)
{
    char *rdest = dest;
    while (*dest) dest++;
    while ((*dest++ = *src++));
    return rdest;
}

char *my_strcpy(char *dest, char *src)
{
    char *start = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return start;
}

void my_memcpy(void *dest, void *src, int n)
{
    char *csrc = (char *)src; 
    char *cdest = (char *)dest;
    for (int i = 0; i < n; i++) cdest[i] = csrc[i];
}

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}