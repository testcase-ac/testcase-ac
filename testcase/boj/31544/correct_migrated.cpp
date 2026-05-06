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
    ll n,m,k,r=0;
    cin>>n>>m>>k;
    for(ll i=1;i<=k;i++) if(k/gcd(i,k)%2) r=(r+pw(2,n*m/(lcm(i,k)/i)))%M;
    cout<<(r*pw(k,M-2)+M-1)%M;
}
