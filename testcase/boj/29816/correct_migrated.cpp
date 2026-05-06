#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    ll n,k,r=0;
    cin>>n;
    n*=2023;
    k=7;
    for(ll i=1;i<=k;i++) if(k/gcd(i,k)%2) r=(r+pw(2,n/(lcm(i,k)/i)))%M;
    ll x=(r*pw(k,M-2)+M-1)%M;
    k=17;r=0;
    for(ll i=1;i<=k;i++) if(k/gcd(i,k)%2) r=(r+pw(2,n/(lcm(i,k)/i)))%M;
    ll y=(r*pw(k,M-2)+M-1)%M;
    k=7*17;r=0;
    for(ll i=1;i<=k;i++) if(k/gcd(i,k)%2) r=(r+pw(2,n/(lcm(i,k)/i)))%M;
    ll z=(r*pw(k,M-2)+M-1)%M;
    r=(pw(2,n)-x-y+z-1)%M;
    if(r<0) r+=M;
    cout<<r;
}
