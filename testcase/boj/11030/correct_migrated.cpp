#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll> p;
ll phi(ll n) {
    ll r=n;
    for(ll i=2;i*i<=n;i++) {
        if(n%i==0) {
            r=r/i*(i-1);
            while(n%i==0) n=n/i;
        }
    } if(n>1) r=r/n*(n-1);
    return r;
}
ll f(ll x,ll m) {return x<m?x:x%m+m;}
ll pw(ll a,ll n,ll m) {
    ll r=1;
    while(n) {
        if(n%2) r=f(r*a,m);
        a=f(a*a,m);
        n/=2;
    } return r;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    p.push_back(100000000);
    while(p.back()>1) p.push_back(phi(p.back()));
    ll a,b,r=1;
    cin>>a>>b;
    vector<ll> x(b,a);
    for(ll i=min(x.size(),p.size())-1;i>=0;i--) r=pw(f(x[i],p[i]),r,p[i]);
    r%=p[0];
    if(a==1||b==1||(a==2&&b<5)||(a>2&&a<9&&b<3)) cout<<r;
    else {
        string s=to_string(r);
        for(int i=s.length();i<8;i++) cout<<0;
        cout<<s;
    }
}
