#include <stdio.h>
#define rep(i,a,b) for(int i=a;i<b;i++)

long long ansDict[36000];

int main() {
    long long X,Q;
    scanf("%lld %lld", &X, &Q);

    for(long long empN = 1; empN < 36000; empN++) {
        X += empN -(X%empN);
        ansDict[empN] = X;
    }
    ansDict[0] = ansDict[35999] / 35999;

    rep(i,0,Q) {
        long long quer;
        scanf("%lld", &quer);
        if (quer < 36000) printf("%lld\n", ansDict[quer]);
        else printf("%lld\n", quer * ansDict[0]);
    }

    return 0;
}
