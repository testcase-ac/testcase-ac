#include <stdio.h>
int fb[1009] = {0,1,1};
int main()
{
    int i, n;
    scanf("%d", &n);
    for (i=3; i<=52; i++) {
        fb[i] = fb[i-1] + fb[i-2]+1;
        fb[i]%=1000000007;
    }
    printf("%d", fb[n+1]);
    return 0;
}
