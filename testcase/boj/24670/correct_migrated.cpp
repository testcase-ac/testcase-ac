#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1000000007;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M;
        a=a*a%M;
        n>>=1;
    } return r;
}
int main() {
    ll n,m,k,r=1,p=1;
    cin>>n>>m>>k;
    for(ll x=1;x<=n;x++) {
        for(ll y=1;y<=m;y++) {
            for(ll z=1;z<=k;z++) {
                r=r*(x+y+z-1)%M;
                p=p*(x+y+z-2)%M;
            }
        }
    } cout<<r*pw(p,M-2)%M;
}
