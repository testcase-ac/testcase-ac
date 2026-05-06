#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=998244353;
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
vector<ll> mulmult(vector<vector<ll>> v) {
    if(v.size()==1) return v[0];
    int n=1;
    while(n<v.size()) n<<=1;
    for(int i=v.size();i<n;i++) v.push_back({1});
    vector<vector<ll>> a(v.begin(),v.begin()+n/2),b(v.begin()+n/2,v.end());
    return mult(mulmult(a),mulmult(b));
}
int main() {
    int n;
    cin>>n;
    vector<vector<ll>> v;
    ll d,md=1e9,ans=0;
    while(n--) {
        cin>>d;
        md=min(md,d);
        v.push_back({1,M-pw(d,M-2)});
    } auto r=mulmult(v);
    for(int i=0;i<r.size();i++) r[i]=(M-r[i])%M;
    r[0]++;
    for(int i=0;i<r.size();i++) ans=(ans+(r[i]*i)%M*pw(i+1,M-2)%M*pw(md,i+1)%M)%M;
    cout<<ans;
}
