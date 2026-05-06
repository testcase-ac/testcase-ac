#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=998244353;
struct Zi {
    ll a=0,b=0;
    Zi operator+(const Zi&x) const {
        ll A=a+x.a,B=b+x.b;
        if(A>=M) A-=M;
        if(B>=M) B-=M;
        return Zi{A,B};
    } Zi operator-(const Zi&x) const {
        ll A=a-x.a,B=b-x.b;
        if(A<0) A+=M;
        if(B<0) B+=M;
        return Zi{A,B};
    } Zi operator*(const Zi&x) const {
        ll A=a*x.a%M,B=b*x.b%M,C=(a*x.b+b*x.a)%M;
        ll X=A-B;
        if(X<0) X+=M;
        return Zi{X,C};
    } Zi operator*(const ll&x) const {return Zi{a*x%M,b*x%M};}
};
Zi pw(Zi a,ll n) {
    Zi r={1,0};
    while(n) {
        if(n&1) r=r*a;
        a=a*a;
        n>>=1;
    } return r;
}
ll ipw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M;
        a=a*a%M;
        n>>=1;
    } return r;
}
void fft(vector<Zi>& a,bool inv) {
	int n=a.size(),j=0;
	for(int i=1;i<n;i++) {
		int bit=n>>1;
		while(j&bit) j^=bit,bit>>=1;
		j^=bit;
		if(i<j) swap(a[i],a[j]);
	} for(int l=2;l<=n;l<<=1) {
		ll w=ipw(3,(M-1)/l);
		if(inv) w=ipw(w,M-2);
		for(int i=0;i<n;i+=l) {
			ll x=1;
			for(int j=0;j<l/2;j++) {
				Zi u=a[i+j];
				Zi v=a[i+j+l/2]*x;
				a[i+j]=u+v;
				a[i+j+l/2]=u-v;
				x=x*w%M;
			}
		}
	} if(inv) {
		ll i=ipw(n,M-2);
		for(Zi&x:a) x=x*i;
	}
}
vector<Zi> mult(vector<Zi> a,vector<Zi> b) {
	ll n=1;
	while(n<a.size()+b.size()) n<<=1;
	a.resize(n);
	b.resize(n);
	fft(a,0);
	fft(b,0);
	for(ll i=0;i<n;i++) a[i]=a[i]*b[i];
	fft(a,1);
	return a;
}
vector<Zi> mulmult(vector<vector<Zi>> v) {
    if(v.size()==1) return v[0];
    int n=1;
    while(n<v.size()) n<<=1;
    for(int i=v.size();i<n;i++) v.push_back({Zi{1,0}});
    vector<vector<Zi>> a(v.begin(),v.begin()+n/2),b(v.begin()+n/2,v.end());
    return mult(mulmult(a),mulmult(b));
}
int main() {
    int n;
    ll r;
    cin>>n>>r;
    vector<vector<Zi>> v;
    while(n--) {
        ll x,y;
        cin>>x>>y;
        x=(M-x)%M;y=(M-y)%M;
        vector<Zi> t={{x,y},{1,0}};
        v.push_back(t);
    } auto t=mulmult(v);
    vector<ll> a(t.size());
    for(int i=0;i<t.size();i++) a[i]=(t[i].a*t[i].a+t[i].b*t[i].b)%M;
    ll ans=0;
    for(ll i=0;i<a.size();i++) ans+=a[i]*ipw(r,i*2)%M*ipw(i+1,M-2)%M;
    cout<<ans%M;
}
