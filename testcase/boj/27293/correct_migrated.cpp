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
ll inv(ll n) {return pw(n,M-2);}
ll f[110000];
ll lagrange(vector<ll> y,ll k) {
    int n=y.size();
    ll t=1,r=0;
    for(int i=0;i<n;i++) t=(t*(k-i+M))%M;
    for(int i=0;i<n;i++) {
        ll p=t*inv(k-i+M)%M;
        ll q=f[i]*f[n-i-1]%M;
        if((n-i-1)%2) q=M-q;
        ll c=y[i]*inv(q)%M;
        r=(r+p*c)%M;
    } return r;
}
int main() {
    f[0]=1;
    for(int i=1;i<110000;i++) f[i]=f[i-1]*i%M;
    int q;
    ll a,b,d;
    cin>>q;
    while(q--) {
        cin>>a>>b>>d;
        vector<ll> y(d+2);
        y[0]=0;
        for(int i=1;i<d+2;i++) y[i]=(y[i-1]+pw(i,d))%M;
        cout<<(lagrange(y,b)-lagrange(y,a-1)+M)%M<<'\n';
    }
}
