#include <stdio.h>
#define rep(i,n) for(int i=0; i<(n); i++)
#define ll long long
ll n;
int m;
int arr[10000];
ll compute(ll mid) {
        ll ret = 0;
        rep(i,m) ret += mid / arr[i];
        return ret + m;
}
int main() {
        scanf("%lld%d", &n, &m);
        rep(i,m) scanf("%d", arr+i);
        ll l = 0, r = 7e11, mid;
        while(l < r) {
                mid = (l+r)/2;
                ll val = compute(mid);
                if(val >= n) {
                        r = mid;
                } else {
                        l = mid+1;
                }
        }
        //printf("bs end at l=%lld\n", l);
        ll diff = compute(l)-n;
        for(int i=m-1;i>=0;i--) {
                if(l % arr[i] == 0) {
                        diff--;
                        if(diff < 0)
                                return !printf("%d\n", i+1);
                }
        }
}
