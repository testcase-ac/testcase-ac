#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll mul(ll a,ll b,ll m) {
    a%=m;b%=m;
	ll r=a*b-m*(ll)(1.L/m*a*b);
	return r+m*(r<0)-m*(r>=m);
}
ll pw(ll x,ll y,ll m) {
    x%=m;
    ll r=1;
    while(y) {
        if(y%2) r=mul(r,x,m);
        x=mul(x,x,m);
        y/=2;
    } return r;
}
bool chk(ll n,ll a) {
    if(a%n==0) return 1;
    ll k=n-1;
    while(1) {
        ll t=pw(a,k,n);
        if(t==n-1) return 1;
        if(k%2) return (t==1||t==n-1);
        k/=2;
    }
}
bool isprime(ll n) {
    if(n<2||n%6%4!=1) return (n|1)==3;
    ll a[]={2,325,9375,28178,450775,9780504,1795265022};
    for(int i=0;i<7;i++) if(!chk(n,a[i])) return 0;
    return 1;
}
ll bgcd(ll a,ll b) {
    if(!a) return b;
    if(!b) return a;
    int s=__builtin_ctz(a|b);
    a>>=__builtin_ctz(a);
    do {
        b>>=__builtin_ctz(b);
        if(a>b) {
            ll t=b;
            b=a;a=t;
        } b=b-a;
    } while(b);
    return a<<s;
}
ll dv(ll n) {
    if(n%2==0) return 2;
    if(isprime(n)) return n;
    auto f=[n](ll x) {return (mul(x,x,n)+1)%n;};
    ll x=0,y=0,t=30,i=1,p=2,q;
    while(t++%40||bgcd(p,n)==1) {
        if(x==y) x=++i,y=f(x);
        if((q=mul(p,max(x,y)-min(x,y),n))) p=q;
        x=f(x);y=f(f(y));
    } return dv(bgcd(p,n));
}
set<ll> factor(ll n) {
    if(n==1) return {};
    if(isprime(n)) return {n};
    ll x=dv(n);
    auto a=factor(x),b=factor(n/x);
    set<ll> s;
    for(ll i:a) s.insert(i);
    for(ll i:b) s.insert(i);
    return s;
}
int main() {
    vector<bool> isp(1000001,1);
    for(int i=2;i*i<1000001;i++) if(isp[i]) for(int j=i*i;j<1000001;j+=i) isp[j]=0;
    vector<ll> p;
    for(int i=2;i<1000001;i++) if(isp[i]) p.push_back(i);
    int n;
    ll a;
    map<ll,int> m;
    cin>>n;
    while(n--) {
        cin>>a;
        for(ll i:p) {
            if(a%i==0) {
                while(a%i==0) a/=i;
                m[i]++;
            }
        } if(a>1) {
            auto s=factor(a);
            for(ll i:s) m[i]++;
        }
    } int mx=0;
    for(auto p:m) mx=max(mx,p.second);
    cout<<mx;
}
