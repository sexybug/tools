#include <stdio.h>
#include <string.h>

/**
 * 提取字符串中的16进制字符，过滤掉非16进制字符
*/
void filter_hex_num(const char* str, int str_len, char* out, int* out_len)
{
    int n=0;
    for(int i=0;i<strlen(str);i++)
    {
        if(((str[i]>='0')&&(str[i]<='9'))||
            ((str[i]>='a')&&(str[i]<='f'))||
            ((str[i]>='A')&&(str[i]<='F')))
        {
            out[n]=str[i];
            n++;
        }
    }
    *out_len=n;
}

int main()
{
    char str[5000]="-1a-F2-";
    char out[5000]={0};
    int out_len=0;

    filter_hex_num(str,strlen(str),out,&out_len);

    printf("%s\n",out);
    
    return 0;
}