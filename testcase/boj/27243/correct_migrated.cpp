#include <bits/stdc++.h>
using namespace std;
int main() {
    long x;
    int k;
    cin>>x>>k;
    int t=__builtin_popcountll(x);
    if(t==k) cout<<0;
    else if(t<k) {
        long r=0;
        for(int i=0;;i++) {
            if(x&(1LL<<i)) continue;
            r+=(1LL<<i);
            t++;
            if(t==k) break;
        } cout<<r;
    } else {
        long r=x,ans=9e18;
        for(int i=0;i<61;i++) {
            if(r&(1LL<<i)) continue;
            r+=(1LL<<i);
            r-=r%(1LL<<i);
            if(__builtin_popcountll(r)<=k) {
                long z=r;
                int p=__builtin_popcountll(r);
                if(p==k) {
                    ans=min(ans,z-x);
                    continue;
                } for(int j=0;;j++) {
                    if(z&(1LL<<j)) continue;
                    z+=(1LL<<j);
                    p++;
                    if(p==k) break;
                } ans=min(ans,z-x);
            }
        } cout<<ans;
    }
}
