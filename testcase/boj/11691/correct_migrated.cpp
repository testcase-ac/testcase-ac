#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
int main() {
    vector<ll> phi(1000001);
    iota(phi.begin(),phi.end(),0);
    for(int i=2;i<1000001;i++) {
        if(phi[i]==i) for(ll j=i;j<1000001;j+=i) phi[j]-=phi[j]/i;
    } ll n,r=0;
    cin>>n;
    ll s[n+1];
    s[1]=0;
    for(ll i=2;i<=n;i++) s[i]=(s[i-1]+i*i%M*phi[i]/2)%M;
    for(ll i=1;i<=n;i++) r=(r+i*s[n/i])%M;
    cout<<r%M;
}
