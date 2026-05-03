//2550703 卓03 李良玉

int tj_strlen(const char str[])
{
    int len = 0;
    while (str[len] != '\0')
    {
        ++len;
    }
    return len;
}

int tj_strcat(char s1[], const char s2[])
{
    int len1 = tj_strlen(s1);
    int i = 0;
    while (true)
    {
        s1[len1 + i] = s2[i];
        if (s2[i] == '\0')
        {
            break;
        }
        ++i;
    }
    return 0;
}

int tj_strncat(char s1[], const char s2[], const int len)
{
    int len1 = tj_strlen(s1);
    int i = 0;
    while (i < len && s2[i] != '\0')
    {
        s1[len1 + i] = s2[i];
        ++i;
    }
    s1[len1 + i] = '\0';
    return 0;
}

int tj_strcpy(char s1[], const char s2[])
{
    int i = 0;
    while (true)
    {
        s1[i] = s2[i];
        if (s2[i] == '\0')
        {
            break;
        }
        ++i;
    }
    return 0;
}

int tj_strncpy(char s1[], const char s2[], const int len)
{
    int i = 0;
    while (i < len && s2[i] != '\0')
    {
        s1[i] = s2[i];
        ++i;
    }
    // 不追加 '\0'，也不清理剩余内容
    return 0;
}

/* 辅助：转小写（只处理 A-Z） */
static char to_lower_char(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 'a';
    }
    return c;
}

int tj_strcmp(const char s1[], const char s2[])
{
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0')
    {
        ++i;
    }
    return (int)((unsigned char)s1[i]) - (int)((unsigned char)s2[i]);
}

int tj_strcasecmp(const char s1[], const char s2[])
{
    int i = 0;
    while (true)
    {
        char c1 = to_lower_char(s1[i]);
        char c2 = to_lower_char(s2[i]);
        if (c1 != c2 || c1 == '\0' || c2 == '\0')
        {
            return (int)((unsigned char)c1) - (int)((unsigned char)c2);
        }
        ++i;
    }
}

int tj_strncmp(const char s1[], const char s2[], const int len)
{
    int i = 0;
    if (len <= 0)
    {
        return 0;
    }
    while (i < len)
    {
        if (s1[i] != s2[i])
        {
            return (int)((unsigned char)s1[i]) - (int)((unsigned char)s2[i]);
        }
        if (s1[i] == '\0')
        {
            return 0;
        }
        ++i;
    }
    return 0;
}

int tj_strcasencmp(const char s1[], const char s2[], const int len)
{
    int i = 0;
    if (len <= 0)
    {
        return 0;
    }
    while (i < len)
    {
        char c1 = to_lower_char(s1[i]);
        char c2 = to_lower_char(s2[i]);
        if (c1 != c2)
        {
            return (int)((unsigned char)c1) - (int)((unsigned char)c2);
        }
        if (c1 == '\0')
        {
            return 0;
        }
        ++i;
    }
    return 0;
}

int tj_strupr(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 'a' + 'A';
        }
        ++i;
    }
    return 0;
}

int tj_strlwr(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] - 'A' + 'a';
        ++i;
    }
    return 0;
}

int tj_strchr(const char str[], char ch)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ch) return i + 1;  // 位置从 1 开始
        ++i;
    }
    return 0;
}

int tj_strstr(const char str[], const char substr[])
{
    if (substr[0] == '\0')
    {
        return 1;
    }
    int i = 0;
    while (str[i] != '\0')
    {
        int j = 0;
        while (substr[j] != '\0' && str[i + j] != '\0' && str[i + j] == substr[j])
        {
            ++j;
        }
        if (substr[j] == '\0')
        {
            return i + 1;
        }
        ++i;
    }
    return 0;
}

int tj_strrchr(const char str[], const char ch)
{
    int len = tj_strlen(str);
    for (int i = len - 1; i >= 0; --i)
    {
        if (str[i] == ch)
        {
            return i + 1;
        }
    }
    return 0;
}

int tj_strrstr(const char str[], const char substr[])
{
    int len_str = tj_strlen(str);
    int len_sub = tj_strlen(substr);
    if (len_sub == 0)
    {
        return 1;
    }
    if (len_sub > len_str)
    {
        return 0;
    }

    for (int i = len_str - len_sub; i >= 0; --i)
    {
        int j = 0;
        while (j < len_sub && str[i + j] == substr[j])
        {
            ++j;
        }
        if (j == len_sub)
        {
            return i + 1;
        }
    }
    return 0;
}

int tj_strrev(char str[])
{
    int len = tj_strlen(str);
    int i = 0;
    int j = len - 1;
    while (i < j)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        ++i;
        --j;
    }
    return 0;
}
