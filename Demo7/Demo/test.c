/*
@File   : test.c
@Author : pan
@Time   : 2023-11-23 19:16:51
*/
#include <stdio.h>
#include <string.h>

int main()
{
    int i, j, cnt = 0, slen = 0;
    char s[200];
    char m;
    scanf("%s", s);
    slen = strlen(s);
    if (slen > 0)
    {
        for (i = 0; i < slen; i++)
        {
            if (s[i] == '*')
            {
                strcat(s, "*"); // 把*号相加到s字符串的后面
                cnt++;          // 计算前面*号的字符串个数
            }
            else
            {
                break;
            }
        }
        slen = strlen(s);
        if (slen > cnt)
        {
            memmove(s, s + cnt, slen - cnt + 1); // 删除前面的*字符串
        }
    }
    printf("%s", s);
    return 0;
}
