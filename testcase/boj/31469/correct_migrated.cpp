#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1000000007;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n%2) r=r*a%M;
        a=a*a%M;
        n/=2;
    } return r;
}
ll f[101];
ll com(ll n,ll k) {return (((f[n]*pw(f[k],M-2))%M)*pw(f[n-k],M-2))%M;}
ll det(vector<vector<ll>> a) {
    int n=a.size();
    ll r=1;
    for(int i=0;i<n;i++) {
        int p=i;
        while(p<n&&a[p][i]==0) p++;
        if(p==n) return 0;
        if(i!=p) swap(a[i],a[p]),r=M-r;
        r=r*a[i][i]%M;
        ll inv=pw(a[i][i],M-2);
        for(int j=i+1;j<n;j++) {
            ll f=a[j][i]*inv%M;
            for(int k=i;k<n;k++) a[j][k]=(a[j][k]-f*a[i][k])%M;
        }
    } return (r+M)%M;
}
int main() {
    f[0]=1;
    for(int i=1;i<=100;i++) f[i]=f[i-1]*i%M;
    int a,b,c,A,B,C;
    cin>>a>>b>>c>>A>>B>>C;
    if(a!=A||b!=B||c!=C) {cout<<0;return 0;}
    if(b<a) swap(a,b);
    if(c<a) swap(a,c);
    vector<pair<int,int>> s,e;
    for(int i=1;i<a-1;i++) {s.push_back({i,a-i-1});e.push_back({b+i,c+a-1-i});}
    s.push_back({0,a});
    e.push_back({b-1,c+a-1});
    s.push_back({a,0});
    e.push_back({b+a-1,c-1});
    s.push_back({b+a-1,0});
    e.push_back({b+a-1,0});
    s.push_back({0,c+a-1});
    e.push_back({0,c+a-1});
    int k=s.size();
    vector<vector<ll>> m(k,vector<ll>(k));
    for(int i=0;i<k;i++) for(int j=0;j<k;j++) {
        int p=e[j].first-s[i].first,q=e[j].second-s[i].second;
        if(p<0||q<0) m[i][j]=0;
        else m[i][j]=com(p+q,p);
    } cout<<det(m)<<'\n';
}
