#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=998244353;
ll pw(ll a,ll n) {
	ll r=1;
	while(n) {
		if(n%2) r=r*a%M;
		a=a*a%M;
		n/=2;
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
	int sz=1;
	while(sz<a.size()+b.size()-1) sz<<=1;
	a.resize(sz);b.resize(sz);
	fft(a,0);fft(b,0);
	for(int i=0;i<sz;i++) a[i]=a[i]*b[i]%M;
	fft(a,1);
	return a;
}
int n,k;
ll v[2000001]={0,1,1};
vector<tuple<int,int,int>> b[2000001];
void upd(int l1,int r1,int l2,int r2,int p) {
	if(r1-l1<300) {
		for(int i=0;i<r1-l1;i++) for(int j=0;j<r1-l1;j++) v[p+i+j]=(v[p+i+j]+v[l1+i]*v[l2+j])%M;
	} else {
		vector<ll> a(v+l1,v+r1),c(v+l2,v+r2);
		vector<ll> d=mult(a,c);
		for(int i=0;i<d.size();i++) v[p+i]=(v[p+i]+d[i])%M;
	}
}
void f(int i) {
	if(i<=k) {
		for(int j=1;j<i;j++) v[i+j]=(v[i+j]+v[i]*2%M*v[j]%M)%M;
		v[2*i]=v[i]*v[i]%M;
	} else {
		int s=log2(i-k+1);
		int x=i-k+2-(1<<s);
		int a=__builtin_ctz((x-1)%(1<<(s-1))+1)+1;
		int t=(x%2)?0:__builtin_ctz(x/2)+1;
		for(int j=1;j<=k;j++) v[i+j]=(v[i+j]+v[i]*v[j]%M)%M;
		for(int z=0;z<b[i].size();z++) {
			int l,r,p;
			tie(l,r,p)=b[i][z];
			upd(l,l+(1<<p),r,r+(1<<p),l+r);
		} b[i].clear();
		int p=i-k,q=k+1;
		for(int j=0;j<a;j++) {
			if(p+(1<<j)-1<=i&&q+(1<<j)-1<=i) upd(p,p+(1<<j),q,q+(1<<j),p+q);
			else b[p+q].push_back({p,q,j});
			p-=1<<j;
			q+=1<<j;
		} p=i-k;q=k+p;
		for(int j=0;j<t;j++) {
			if(p+(1<<j)-1<=i&&q+(1<<j)-1<=i) upd(p,p+(1<<j),q,q+(1<<j),p+q);
			else b[p+q].push_back({p,q,j});
			p-=1<<j;
			q-=1<<(j+1);
		}
	}
}
int main() {
	cin>>n>>k;
	for(int i=2;i<=n;i++) f(i);
	cout<<v[n];
}
