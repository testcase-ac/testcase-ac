#include <stdio.h>
long long c[200001];
int main()
{
    long long t,i,n,p;
    scanf("%lld",&t);
    while (t--) {
        scanf("%lld%lld",&n,&p);
        for (i=0; i<n; i++){
            scanf("%lld",&c[i]);
        }
        if(c[0]%(p+1)==0)printf("Second\n");
        else printf("First\n");
    }
}
