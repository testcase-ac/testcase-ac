#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=998244353;
ll f[3000001],invf[3000001];
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
int main() {
    f[0]=1;
    for(int i=1;i<3000001;i++) f[i]=f[i-1]*i%M;
    invf[3000000]=pw(f[3000000],M-2);
    for(int i=2999999;i>=0;i--) invf[i]=invf[i+1]*(i+1)%M;
    int t;
    ll a[3];
    cin>>t;
    while(t--) {
        cin>>a[0]>>a[1]>>a[2];
        sort(a,a+3);
        a[2]=min(a[2],a[0]+a[1]);
        ll p,q=1;
        ll x=a[0]+a[1]-a[2],y=a[1]+a[2]-a[0],z=a[2]+a[0]-a[1];
        p=x*y+y*z+z*x;
        for(ll i=0;i<z;i++) q=q*f[x+y+i]%M*f[i]%M*invf[x+i]%M*invf[y+i]%M;
        cout<<p<<' '<<q<<'\n';
    }
}
