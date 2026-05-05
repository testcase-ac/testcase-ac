#include <stdio.h>
int main()
{
    int i, n, endz=0, stz=0;
    long long c[250009] = {0}, sum=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%lld", &c[i]);
        sum += c[i];
    }
    for (i=0; i<n; i++) {
        if (c[i]==0) stz++;
        else break;
    }
    for (i=n-1; i>=0; i--) {
        if (c[i]==0) endz++;
        else break;
    }
    if (sum==0&&n%2==1) {
        printf("%d", n/2);
    }
    else {
        for (i=0; i<n; i++) {
            if (i!=n-1) {
                if (c[i]==0&&c[i+1]!=0) {
                    sum++;
                }
                else if (c[i]==0&&c[i+1]==0) {
                    sum++;
                    c[i+1]=1;
                }
            }
            else if (c[i]==0) {
                sum++;
            }
        }
        if (c[0]==0&&c[n-1]==0&&endz%2==stz%2) {
            sum--;
        }
        printf("%lld", sum);
    }
    return 0;
}
