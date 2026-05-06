#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=998244353;
ll f[200001];
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
ll com(ll n,ll k) {return (((f[n]*pw(f[k],M-2))%M)*pw(f[n-k],M-2))%M;}
int main() {
    f[0]=1;
    for(int i=1;i<=200000;i++) f[i]=f[i-1]*i%M;
    ll n,m,x;
    cin>>n>>m;
    x=com(n+m-2,m-1);
    x=(x*x-com(n+m-2,m-2)*com(n+m-2,m))%M;
    if(x<0) x+=M;
    cout<<x;
}
