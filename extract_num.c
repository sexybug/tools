#include <stdio.h>
#include <string.h>

/**
 * 提取0x字符串中的16进制字符。提取每个"0x"后的两个16进制字符。
 */
void extract_0x_hex(const char *str, int str_len, char *out, int *out_len)
{
    int n = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '0' && str[i + 1] == 'x')
        {
            out[n] = str[i + 2];
            out[n + 1] = str[i + 3];
            n += 2;
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

/**
 * 提取任意字符串中的16进制字符。
 */
void extract_hex(const char *str, int str_len, char *out, int *out_len)
{
    if ((str[0] == '{') ||
        (str[0] == '0' && str[1] == 'x'))
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
    *str_len = n;
}

int main()
{
    char str[5000] = "0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,\
			0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x01, 0x02,\
			0x03, 0x04, 0x05, 0x06, 0x07, abc0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D,\
			0x0E, 0x0F";
    char out[5000] = {0};
    int in_len = 0, out_len = 0;

    printf("input string:\n");
    input_string(str, &in_len);
    // printf("%s\n", str);

    extract_hex(str, strlen(str), out, &out_len);

    printf("hex-number bytes: %d\n", out_len / 2);
    printf("%s\n", out);

    return 0;
}