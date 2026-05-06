#include <bits/stdc++.h>
#define ll __int128
using namespace std;
const ll M=(ll)1e18+3;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
ll psqrt(ll n) {
    if(pw(n,(M-1)/2)!=1) return -1;
    return pw(n,(M+1)/4);
}
int main() {
    int n;
    cin>>n;
    vector<ll> a(n,0),b(n,0);
    for(int i=0;i<n;i++) {
        string s;
        ll t=0;
        cin>>s;
        for(char c:s) t=(t*10+c-'0')%M;
        ll x=psqrt(t);
        if(x<0) b[i]=psqrt(t*2%M);
        else a[i]=x;
    } int l=n/2;
    map<pair<ll,ll>,int> m;
    long r=0;
    for(int i=0;i<(1<<l-1);i++) {
        ll x=a[0],y=b[0];
        for(int j=1;j<l;j++) {
            if(i&(1<<j-1)) {x+=a[j];y+=b[j];}
            else {x+=M-a[j];y+=M-b[j];}
        } m[{x%M,y%M}]++;
    } for(int i=0;i<(1<<n-l);i++) {
        ll x=0,y=0;
        for(int j=l;j<n;j++) {
            if(i&(1<<j-l)) {x+=a[j];y+=b[j];}
            else {x+=M-a[j];y+=M-b[j];}
        } r+=m[{x%M,y%M}];
    } cout<<r;
}
