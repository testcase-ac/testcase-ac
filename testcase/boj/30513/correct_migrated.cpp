#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll f[200001],invf[200001];
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M;
        a=a*a%M;
        n>>=1;
    } return r;
}
ll com(ll n,ll r) {return f[n]*invf[r]%M*invf[n-r]%M;}
int main() {
    f[0]=1;
    for(int i=1;i<200001;i++) f[i]=f[i-1]*i%M;
    invf[200000]=pw(f[200000],M-2);
    for(int i=199999;i>=0;i--) invf[i]=invf[i+1]*(i+1)%M;
    int m,n;
    cin>>m>>n;
    ll s=0;
    for(int i=0;i<n/m;i++) s=(s+com(n-m*i,n-m*(i+1)))%M;
    for(int i=0;i<n;i++) s=(s+com(n+m-i-1,n-i-1))%M;
    cout<<s;
}
