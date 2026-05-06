#include <bits/stdc++.h>
#define ll long long
#define lll __int128
using namespace std;
ll P;
const ll M1=998244353,M2=2281701377,M3=1092616193;
ll npw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M1;
        a=a*a%M1;
        n>>=1;
    } return r;
}
ll npw2(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M2;
        a=a*a%M2;
        n>>=1;
    } return r;
}
ll npw3(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M3;
        a=a*a%M3;
        n>>=1;
    } return r;
}
void fft(vector<ll>&a,bool inv) {
    int n=a.size(),j=0;
    for(int i=1;i<n;i++) {
        int bit=n>>1;
        while(j&bit) j^=bit,bit>>=1;
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    } for(int l=2;l<=n;l<<=1) {
        ll wl=npw(3,(M1-1)/l);
        if(inv) wl=npw(wl,M1-2);
        int h=l/2;
        for(int i=0;i<n;i+=l) {
            ll w=1,*ai=&a[i];
            for(int j=0;j<h;j++) {
                ll u=ai[j],v=ai[j+h]*w%M1;
                ai[j]=u+v;
                if(ai[j]>=M1) ai[j]-=M1;
                ai[j+h]=u-v;
                if(ai[j+h]<0) ai[j+h]+=M1;
                w=w*wl%M1;
            }
        }
    } if(inv) {
        ll iv=npw(n,M1-2);
        for(ll &i:a) i=i*iv%M1;
    }
}
void fft2(vector<ll>&a,bool inv) {
    int n=a.size(),j=0;
    for(int i=1;i<n;i++) {
        int bit=n>>1;
        while(j&bit) j^=bit,bit>>=1;
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    } for(int l=2;l<=n;l<<=1) {
        ll wl=npw2(3,(M2-1)/l);
        if(inv) wl=npw2(wl,M2-2);
        int h=l/2;
        for(int i=0;i<n;i+=l) {
            ll w=1,*ai=&a[i];
            for(int j=0;j<h;j++) {
                ll u=ai[j],v=ai[j+h]*w%M2;
                ai[j]=u+v;
                if(ai[j]>=M2) ai[j]-=M2;
                ai[j+h]=u-v;
                if(ai[j+h]<0) ai[j+h]+=M2;
                w=w*wl%M2;
            }
        }
    } if(inv) {
        ll iv=npw2(n,M2-2);
        for(ll &i:a) i=i*iv%M2;
    }
}
void fft3(vector<ll>&a,bool inv) {
    int n=a.size(),j=0;
    for(int i=1;i<n;i++) {
        int bit=n>>1;
        while(j&bit) j^=bit,bit>>=1;
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    } for(int l=2;l<=n;l<<=1) {
        ll wl=npw3(3,(M3-1)/l);
        if(inv) wl=npw3(wl,M3-2);
        int h=l/2;
        for(int i=0;i<n;i+=l) {
            ll w=1,*ai=&a[i];
            for(int j=0;j<h;j++) {
                ll u=ai[j],v=ai[j+h]*w%M3;
                ai[j]=u+v;
                if(ai[j]>=M3) ai[j]-=M3;
                ai[j+h]=u-v;
                if(ai[j+h]<0) ai[j+h]+=M3;
                w=w*wl%M3;
            }
        }
    } if(inv) {
        ll iv=npw3(n,M3-2);
        for(ll &i:a) i=i*iv%M3;
    }
}
vector<ll> mult(vector<ll> a,vector<ll> b,int f) {
    ll n=1;
    while(n<a.size()+b.size()) n<<=1;
    a.resize(n);
    b.resize(n);
    if(f==1) {
        fft(a,0);
        fft(b,0);
        for(ll i=0;i<n;i++) a[i]=a[i]*b[i]%M1;
        fft(a,1);
    } else if(f==2) {
        fft2(a,0);
        fft2(b,0);
        for(ll i=0;i<n;i++) a[i]=a[i]*b[i]%M2;
        fft2(a,1);
    } else {
        fft3(a,0);
        fft3(b,0);
        for(ll i=0;i<n;i++) a[i]=a[i]*b[i]%M3;
        fft3(a,1);
    } return a;
}
ll crt(const vector<lll>& v,const vector<ll>& p) {
	lll m=1,r=0;
	for(auto i:p) m*=i;
	for(int i=0;i<v.size();i++) {
		lll mi=m/p[i];
		lll iv;
		if(i==0) iv=npw(mi%p[i],p[i]-2);
		else if(i==1) iv=npw2(mi%p[i],p[i]-2);
		else iv=npw3(mi%p[i],p[i]-2);
		r=(r+v[i]*mi%m*iv%m)%m;
	} return r%P;
}
vector<ll> mul(vector<ll> a,vector<ll> b) {
    auto x=mult(a,b,1);
    auto y=mult(a,b,2);
    auto z=mult(a,b,3);
    ll iv=npw2(M1,M2-2);
    for(int i=0;i<x.size();i++) x[i]=crt({x[i],y[i],z[i]},{M1,M2,M3})%P;
    return x;
}
lll pw(lll a,lll n) {
    lll r=1;
    while(n) {
        if(n%2) r=r*a%P;
        a=a*a%P;
        n/=2;
    } return r;
}
vector<lll> f(300000),invf(300000);
vector<lll> lagrange(vector<lll> a) {
    int d=a.size()-1;
    vector<ll> b(d+1);
	for(int i=0;i<=d;i++) {
		b[i]=a[i]*invf[i]%P*invf[d-i]%P;
		if((d-i)%2) b[i]=P-b[i];
		if(b[i]==P) b[i]=0;
	} vector<ll> x(d*4+2),y(d*4+2);
	for(int i=1;i<d*4+2;i++) x[i]=f[i-1]*invf[i]%P;
	y[d+1]=1;
	for(int i=0;i<=d;i++) y[d+1]=(lll)y[d+1]*(d+1-i)%P;
	for(int i=d+2;i<d*4+2;i++) y[i]=(lll)y[i-1]*i%P*x[i-d-1]%P;
	auto t=mul(b,x);
	vector<lll> r(d*4+2);
	for(int i=0;i<=d;i++) r[i]=a[i];
	for(int i=d+1;i<d*4+2;i++) r[i]=(lll)y[i]*t[i]%P;
	return r;
}
vector<lll> next(vector<lll> a) {
    auto t=lagrange(a);
    vector<lll> r(t.size()/2);
    for(int i=0;i<r.size();i++) r[i]=t[i*2]*t[i*2+1]%P;
    return r;
}
int main() {
    ll n;
    cin>>n>>P;
    f[0]=1;
    int sz=min((ll)P,300000LL);
    for(int i=1;i<sz;i++) f[i]=f[i-1]*i%P;
    invf[sz-1]=pw(f[sz-1],P-2);
    for(int i=sz-2;i>=0;i--) invf[i]=invf[i+1]*(i+1)%P;
    ll d=1;
	vector<lll> v={1,2};
	while(n>d*(d+1)) {
	    v=next(v);
	    d*=2;
	} lll r=1,s=n/d;
	for(int i=0;i<s;i++) r=r*v[i]%P;
	for(lll i=s*d+1;i<=n;i++) r=r*i%P;
	cout<<(ll)r;
}
