//2550703 ×¿03 ÀîÁ¼Óñ
#include "6-b4.h"
#include <cstdio>

static char to_lower_char(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (char)(c - 'A' + 'a');
    return c;
}

static char to_upper_char(char c)
{
    if (c >= 'a' && c <= 'z')
        return (char)(c - 'a' + 'A');
    return c;
}

int tj_strlen(const char* str)
{
    if (str == 0)
        return 0;
    int n = 0;
    const char* p = str;
    while (*p)
    {
        n++;
        p++;
    }
    return n;
}

char* tj_strcat(char* s1, const char* s2)
{
    if (s1 == 0)
        return 0;
    if (s2 == 0)
        return s1;

    char* p = s1;
    while (*p)
        p++;

    const char* q = s2;
    while (*q)
    {
        *p = *q;
        p++;
        q++;
    }
    *p = 0;
    return s1;
}

char* tj_strncat(char* s1, const char* s2, const int len)
{
    if (s1 == 0)
        return 0;
    if (s2 == 0)
        return s1;
    if (len <= 0)
        return s1;

    char* p = s1;
    while (*p)
        p++;

    const char* q = s2;
    int n = len;
    while (n > 0 && *q)
    {
        *p = *q;
        p++;
        q++;
        n--;
    }
    *p = 0;
    return s1;
}

char* tj_strcpy(char* s1, const char* s2)
{
    if (s1 == 0)
        return 0;
    if (s2 == 0)
    {
        *s1 = 0;
        return s1;
    }

    char* p = s1;
    const char* q = s2;
    while (*q)
    {
        *p = *q;
        p++;
        q++;
    }
    *p = 0;
    return s1;
}

char* tj_strncpy(char* s1, const char* s2, const int len)
{
    if (s1 == 0)
        return 0;
    if (s2 == 0)
        return s1;
    if (len <= 0)
        return s1;

    char* p = s1;
    const char* q = s2;
    int n = len;
    while (n > 0 && *q)
    {
        *p = *q;
        p++;
        q++;
        n--;
    }
    return s1;
}

int tj_strcmp(const char* s1, const char* s2)
{
    if (s1 == 0 && s2 == 0)
        return 0;
    if (s1 == 0)
        return -1;
    if (s2 == 0)
        return 1;

    const unsigned char* p = (const unsigned char*)s1;
    const unsigned char* q = (const unsigned char*)s2;

    while (*p && *q && *p == *q)
    {
        p++;
        q++;
    }
    return (int)(*p) - (int)(*q);
}

int tj_strcasecmp(const char* s1, const char* s2)
{
    if (s1 == 0 && s2 == 0)
        return 0;
    if (s1 == 0)
        return -1;
    if (s2 == 0)
        return 1;

    const char* p = s1;
    const char* q = s2;

    while (*p && *q)
    {
        char c1 = to_lower_char(*p);
        char c2 = to_lower_char(*q);
        if (c1 != c2)
            return (int)(unsigned char)c1 - (int)(unsigned char)c2;
        p++;
        q++;
    }
    return (int)(unsigned char)to_lower_char(*p) - (int)(unsigned char)to_lower_char(*q);
}

int tj_strncmp(const char* s1, const char* s2, const int len)
{
    if (len <= 0)
        return 0;
    if (s1 == 0 && s2 == 0)
        return 0;
    if (s1 == 0)
        return -1;
    if (s2 == 0)
        return 1;

    const unsigned char* p = (const unsigned char*)s1;
    const unsigned char* q = (const unsigned char*)s2;
    int n = len;

    while (n > 0)
    {
        if (*p != *q)
            return (int)(*p) - (int)(*q);
        if (*p == 0)
            return 0;
        p++;
        q++;
        n--;
    }
    return 0;
}

int tj_strcasencmp(const char* s1, const char* s2, const int len)
{
    if (len <= 0)
        return 0;
    if (s1 == 0 && s2 == 0)
        return 0;
    if (s1 == 0)
        return -1;
    if (s2 == 0)
        return 1;

    const char* p = s1;
    const char* q = s2;
    int n = len;

    while (n > 0)
    {
        char c1 = to_lower_char(*p);
        char c2 = to_lower_char(*q);
        if (c1 != c2)
            return (int)(unsigned char)c1 - (int)(unsigned char)c2;
        if (*p == 0)
            return 0;
        p++;
        q++;
        n--;
    }
    return 0;
}

char* tj_strupr(char* str)
{
    if (str == 0)
        return 0;
    char* p = str;
    while (*p)
    {
        *p = to_upper_char(*p);
        p++;
    }
    return str;
}

char* tj_strlwr(char* str)
{
    if (str == 0) return 0;
    char* p = str;
    while (*p)
    {
        *p = to_lower_char(*p);
        p++;
    }
    return str;
}

int tj_strchr(const char* str, const char ch)
{
    if (str == 0)
        return 0;

    if (ch == 0)
        return tj_strlen(str) + 1;

    int pos = 1;
    const char* p = str;
    while (*p)
    {
        if (*p == ch)
            return pos;
        p++;
        pos++;
    }
    return 0;
}

int tj_strstr(const char* str, const char* substr)
{
    if (str == 0 || substr == 0)
        return 0;
    if (*substr == 0)
        return 1;

    int pos = 1;
    const char* p = str;

    while (*p)
    {
        const char* q = p;
        const char* r = substr;
        while (*r && *q && *q == *r)
        {
            q++;
            r++;
        }
        if (*r == 0)
            return pos;
        p++;
        pos++;
    }
    return 0;
}

int tj_strrchr(const char* str, const char ch)
{
    if (str == 0)
        return 0;
    if (ch == 0)
        return tj_strlen(str) + 1;

    int pos = 1;
    int last = 0;
    const char* p = str;

    while (*p)
    {
        if (*p == ch)
            last = pos;
        p++;
        pos++;
    }
    return last;
}

int tj_strrstr(const char* str, const char* substr)
{
    if (str == 0 || substr == 0)
        return 0;
    if (*substr == 0)
        return 1;

    int pos = 1;
    int last = 0;
    const char* p = str;

    while (*p)
    {
        const char* q = p;
        const char* r = substr;
        while (*r && *q && *q == *r)
        {
            q++;
            r++;
        }
        if (*r == 0)
            last = pos;

        p++;
        pos++;
    }
    return last;
}

char* tj_strrev(char* str)
{
    if (str == 0)
        return 0;

    char* end = str;
    while (*end)
        end++;

    char* l = str;
    char* r = end - 1;

    while (l < r)
    {
        char t = *l;
        *l = *r;
        *r = t;
        l++;
        r--;
    }
    return str;
}
