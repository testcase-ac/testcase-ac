#include <bits/stdc++.h>
#define ll long long
using namespace std;
using cd=complex<double>;
const double pi=acos(-1);
void fft(vector<cd> &a,bool inv) {
	ll n=a.size();
	for(ll i=1,j=0;i<n;i++) {
		ll bit=n>>1;
		while(j>=bit) {
			j-=bit;
			bit>>=1;
		} j+=bit;
		if(i<j) swap(a[i],a[j]);
	} for(ll i=1;i<n;i<<=1) {
		double ang=(inv?-1:1)*pi/i;
		cd w={cos(ang),sin(ang)};
		for(ll j=0;j<n;j+=i<<1) {
			cd th={1,0};
			for(ll k=0;k<i;k++) {
				cd tmp=a[i+j+k]*th;
				a[i+j+k]=a[j+k]-tmp;
				a[j+k]+=tmp;
				th*=w;
			}
		}
	} if(inv) for(ll i=0;i<n;i++) a[i]/=n;
}
vector<ll> mult(vector<ll> a,vector<ll> b) {
	vector<cd> fa(a.begin(),a.end()),fb(b.begin(),b.end());
	ll n=1;
	while(n<a.size()+b.size()) n<<=1;
	fa.resize(n);
	fb.resize(n);
	fft(fa,0);
	fft(fb,0);
	for(ll i=0;i<n;i++) fa[i]*=fb[i];
	fft(fa,1);
	vector<ll> r(n);
	for(ll i=0;i<n;i++) r[i]=(ll)round(fa[i].real());
	return r;
}
int main() {
    string s;
    cin>>s;
    vector<int> v(s.length()+1);
    v[0]=0;
    for(int i=1;i<=s.length();i++) v[i]=v[i-1]+s[i-1]-'a'+1;
    int n=v.back();
    vector<ll> a(n+1,0),b(n+1);
    for(int i:v) a[i]=1;
    for(int i=0;i<=n;i++) b[i]=a[n-i];
    a=mult(a,b);
    int k=0;
    for(int i=1;i<=n;i++) if(a[i]) k++;
    cout<<k;
}
