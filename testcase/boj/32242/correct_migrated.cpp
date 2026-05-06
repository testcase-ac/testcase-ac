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
int main() {
    ll a,b,c,d;
    cin>>a>>b>>c>>d;
    if(a==0) {
        if(b&&c) {
            if(d%gcd(abs(b),abs(c))) cout<<0;
            else cout<<"INFINITY";
        } else if(b==0&&c==0) {
            if(d) cout<<0;
            else cout<<"INFINITY";
        } else if(b==0) {
            if(d%c) cout<<0;
            else cout<<"INFINITY";
        } else {
            if(d%b) cout<<0;
            else cout<<"INFINITY";
        } return 0;
    } if(b==0&&c==0) {
        if(d%a) {cout<<0;return 0;}
        d/=-a;
        set<pair<ll,ll>> s;
        ll absd=abs(d);
        if(d==0) {cout<<"INFINITY";return 0;}
        else for(ll i=1;i*i<=absd;i++) {
            if(d%i==0) {
                s.insert({i,d/i});
                s.insert({d/i,i});
                s.insert({-i,-d/i});
                s.insert({-d/i,-i});
            }
        } cout<<s.size()<<'\n';
        for(auto p:s) cout<<p.first<<' '<<p.second<<'\n';
        return 0;
    } if(b*c-a*d==0) {
        if(b%a&&c%a) cout<<0;
        else cout<<"INFINITY";
        return 0;
    } else {
        ll x=b*c-a*d,n=abs(x);
        map<ll,int> m;
        while(n>1) {
            ll d=dv(n);
            m[d]++;
            n/=d;
        } vector<ll> d={1};
        for(auto p:m) {
            int t=d.size();
            for(int i=0;i<t;i++) {
                for(int j=1;j<=p.second;j++) d.push_back(d[i]*pw(p.first,j,1e30));
            }
        } vector<pair<ll,ll>> dd,r;
        for(ll i:d) {
            dd.push_back({i,x/i});
            dd.push_back({-i,-x/i});
        } for(auto p:dd) {
            if((p.first-c)%a==0&&(p.second-b)%a==0) r.push_back({(p.first-c)/a,(p.second-b)/a});
        } sort(r.begin(),r.end());
        cout<<r.size()<<'\n';
        for(auto p:r) cout<<p.first<<' '<<p.second<<'\n';
    }
}
