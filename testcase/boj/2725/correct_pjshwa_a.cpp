#include <stdio.h>
int main() {
    int c,n,a[1001]={0,3},top=2;
    scanf("%d",&c);
    for(int k=1;k<=c;k++) {
        scanf("%d",&n);
        for(;top<=n;top++) {
            double ret=top;
            int t=top;
            for(int i=2;t>1;i++) {
                if(t%i==0) {
                    ret*=(double)(i-1)/i;
                    while(t%i==0) t/=i;
                }
            }
            a[top]=a[top-1]+ret*2;
        }
        printf("%d\n",a[n]);
    }
    return 0;
}
