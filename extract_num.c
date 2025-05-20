#include <stdio.h>
#include <string.h>
#include "test.h"

// 判断字符是否为十六进制字符
int is_hex_char(char c)
{
    // 如果字符在0-9之间，或者a-f之间，或者A-F之间，则返回1，否则返回0
    if ((c >= '0' && c <= '9') ||
        (c >= 'a' && c <= 'f') ||
        (c >= 'A' && c <= 'F'))
    {
        return 1;
    }
    return 0;
}

/**
 * 提取0x字符串中的16进制字符。提取每个"0x"后的所有16进制字符，直到遇到非16进制字符。
 */
void extract_0x_hex(const char *str, int str_len, char *out, int *out_len)
{
    int i = 0;
    int n = 0;
    int k = 0;

    // 提取0x字符串中的16进制字符
    while(i < str_len)
    {
        if (str[i] == '0' && str[i + 1] == 'x')
        {
            k = 2;
            while (is_hex_char(str[i + k]))
            {
                out[n] = str[i + k];
                n++;
                k++;
            }
            i += k;
        }
        else
        {
            i++;
        }
    }
    *out_len = n;
}

/**
 * 提取字符串中的16进制字符。过滤掉非16进制字符，保留所有16进制字符。
 */
void extract_any_hex(const char *str, int str_len, char *out, int *out_len)
{
    int n = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (((str[i] >= '0') && (str[i] <= '9')) ||
            ((str[i] >= 'a') && (str[i] <= 'f')) ||
            ((str[i] >= 'A') && (str[i] <= 'F')))
        {
            out[n] = str[i];
            n++;
        }
    }
    *out_len = n;
}

int contain_0x(const char *str, int str_len)
{
    int i = 0;
    while (i < str_len - 1)
    {
        if (str[i] == '0' && str[i + 1] == 'x')
        {
            return 1;
        }
        else
        {
            i++;
        }
    }
    return 0;
}

/**
 * 提取任意字符串中的16进制字符。
 */
void extract_hex(const char *str, int str_len, char *out, int *out_len)
{
    if (contain_0x(str, str_len))
    {
        extract_0x_hex(str, str_len, out, out_len);
    }
    else
    {
        extract_any_hex(str, str_len, out, out_len);
    }
}

/**
 * 输入任意长度字符串。通过两个换行结束输入。
 */
void input_string(char *str, int *str_len)
{
    int n = 0;
    int line = 0;
    char c;
    while (1)
    {
        scanf("%c", &c);
        if (c == '\n')
        {
            line++;
            if (line == 2)
            {
                break;
            }
        }
        else
        {
            line = 0;
        }
        str[n] = c;
        n++;
    }
    // 设置字符串结束标志
    str[n] = 0;
    *str_len = n;
}

int main()
{
    char str[5000] = {0};
    char out[5000] = {0};
    int in_len = 0, out_len = 0;

    while (1)
    {
        printf("input string:\n");
        input_string(str, &in_len);
        // printf("%s\n", str);

        extract_hex(str, strlen(str), out, &out_len);
        // 避免out没有结束符
        out[out_len] = 0;

        printf("hex-number bytes: %d\n", out_len / 2);
        print_string(out, out_len, 64);
    }

    return 0;
}