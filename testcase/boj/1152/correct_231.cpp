#include <stdio.h>
#include <string.h>

int main()
{
    char input[1000002] = {};
    int count  = 0;
    int len;
    fgets(input, sizeof(input), stdin);

    len = strlen(input);

    for(int i = 0; i < len; i++)
    {
        if((input[i] == ' ') && (input[i - 1] != ' '))
            count ++;
    }

    if(input[0] == ' ')
        count --;
    if(input[len - 1] == '\n' && input[len - 2] != ' ')
        count ++;
    if(input[0] == '\n')
        count = 0;

    printf("%d\n", count);

    return 0;
}