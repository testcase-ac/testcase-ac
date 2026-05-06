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
    vector<ll> phi(1000001),f(1000001);
    for(int i=1;i<1000001;i++) {phi[i]=i;f[i]=0;}
    for(int i=2;i<1000001;i++) {
        if(phi[i]==i) for(int j=i;j<1000001;j+=i) phi[j]-=phi[j]/i;
    } ll n,k,r=1;
    cin>>n>>k;
    for(ll i=1;i<1000001;i++) for(ll j=i;j<1000001;j+=i) f[j]=(f[j]+phi[i]*pw(k,j/i))%M;
    for(ll i=1;i<=n;i++) {
        ll t=f[i];
        if(i%2) t+=i*pw(k,(i+1)/2);
        else t+=(i/2)*(pw(k,i/2+1)+pw(k,i/2));
        t%=M;
        r=(r+t*pw(i*2,M-2))%M;
    } cout<<r;
}
