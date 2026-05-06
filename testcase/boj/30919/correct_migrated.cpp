#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll primes(ll n) {
	if(n==1) return 0;
	ll s=sqrt(n),c=(s+1)/2;
	vector<ll> a(c),b(c),v(c);
	vector<bool> no(s+1,0);
	ll p=0;
	for(ll i=0;i<c;i++) {a[i]=i;v[i]=2*i+1;b[i]=(n/(2*i+1)-1)/2;}
	for(ll x=3;x<=s;x+=2) {
		if(no[x]) continue;
		ll q=x*x;
		if(q*q>n) break;
		no[x]=1;
		for(ll i=q;i<=s;i+=2*x) no[i]=1;
		ll y=0;
		for(ll i=0;i<c;i++) {
			if(no[v[i]]) continue;
			ll d=v[i]*x;
			b[y]=b[i]-(d<=s?b[a[(d>>1)]-p]:a[((n/d-1)/2)])+p;
			v[y++]=v[i];
		} c=y;
		ll i=(s-1)/2;
		for(ll j=((s/x)-1)|1;j>=x;j-=2) while(i>=(j*x)>>1) a[i--]-=a[j>>1]-p;
		p++;
	} b[0]+=(c+2*(p-1))*(c-1)/2;
	for(int i=1;i<c;i++) b[0]-=b[i];
	for(int i=1;i<c;i++) {
		ll w=v[i],M=n/w,e=a[(int)((M/w-1)/2)]-p;
		if(e<i+1) break;
		ll t=0;
		for(int j=i+1;j<=e;j++) t+=a[((M/v[j]-1)/2)];
		b[0]+=t-(e-i)*(p+i-1);
	} return b[0]+1;
}
int main() {
	int t;
	ll n;
	cin>>t;
	while(t--) {
		cin>>n;
		cout<<primes(n)<<'\n';
	}
}
