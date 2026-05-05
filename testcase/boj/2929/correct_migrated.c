#include <stdio.h>
#include <string.h>

int main()
{
    char arr[202];
    scanf("%s", arr);
    int seq = 0;
    for(int i = 0; i < strlen(arr); i++)
    {
        if(arr[i] >= 65 && arr[i] <= 90)
        {
            if(seq%4 != 0)
            {
                seq += 4-seq%4;
            }
        }
        seq++;
    }
    printf("%d", seq-(int)strlen(arr));
}
