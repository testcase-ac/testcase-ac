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
    ll n,k,r=1;
    cin>>n>>k;
    vector<ll> phi(n+1),f(n+1);
    vector<ll> p(n+2),inv(2*n+2);
    p[0]=1;
    for(int i=1;i<=n+1;i++) p[i]=p[i-1]*k%M;
    inv[1]=1;
    for(int i=2;i<=2*n;i++) inv[i]=(M-M/i*inv[M%i]%M)%M;
    for(int i=1;i<=n;i++) {phi[i]=i;f[i]=0;}
    for(int i=2;i<=n;i++) {
        if(phi[i]==i) for(int j=i;j<=n;j+=i) phi[j]-=phi[j]/i;
    }
    for(ll i=1;i<=n;i++) for(ll j=i;j<=n;j+=i) f[j]=(f[j]+phi[i]*p[j/i])%M;
    for(ll i=1;i<=n;i++) {
        ll t=f[i];
        if(i%2) t+=i*p[(i+1)/2];
        else t+=(i/2)*(p[i/2+1]+p[i/2]);
        t%=M;
        r=(r+t*inv[i*2])%M;
    } cout<<r;
}
