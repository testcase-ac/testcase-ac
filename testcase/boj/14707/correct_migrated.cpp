#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,l;
ll M=998244353,M1=998244353,M2=2281701377;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M;
        a=a*a%M;
        n>>=1;
    } return r;
}
void fft(vector<ll>& a,bool inv) {
    int n=a.size(),j=0;
    for(int i=1;i<n;i++) {
        int bit=n>>1;
        while(j&bit) j^=bit,bit>>=1;
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    } for(int l=2;l<=n;l<<=1) {
        ll w=pw(3,(M-1)/l);
        if(inv) w=pw(w,M-2);
        for(int i=0;i<n;i+=l) {
            ll x=1;
            for(int j=0;j<l/2;j++) {
                ll u=a[i+j];
                ll v=a[i+j+l/2]*x%M;
                a[i+j]=(u+v)%M;
                a[i+j+l/2]=(u-v+M)%M;
                x=x*w%M;
            }
        }
    } if(inv) {
        ll i=pw(n,M-2);
        for(ll&x:a) x=x*i%M;
    }
}
vector<ll> mult(vector<ll> a,vector<ll> b) {
    ll n=1;
    while(n<a.size()+b.size()) n<<=1;
    a.resize(n);
    b.resize(n);
    fft(a,0);
    fft(b,0);
    for(ll i=0;i<n;i++) a[i]=a[i]*b[i]%M;
    fft(a,1);
    return a;
}
int main() {
    cin>>n>>m>>l;
    vector<ll> a(l,0),b(l,0);
    for(ll i=0;i<n;i++) {
        ll x;
        cin>>x;
        a[i*m%l]+=x;
    } for(ll i=0;i<m;i++) {
        ll x;
        cin>>x;
        b[i%l]+=x;
    } auto c=mult(a,b);
    for(int i=l;i<c.size();i++) c[i%l]+=c[i];
    M=M2;
    auto d=mult(a,b);
    for(int i=l;i<d.size();i++) d[i%l]+=d[i];
    ll iv=pw(M1,M2-2);
    for(int i=0;i<l;i++) cout<<(d[i]-c[i]+M2)%M2*iv%M2*M1+c[i]<<'\n';
}
