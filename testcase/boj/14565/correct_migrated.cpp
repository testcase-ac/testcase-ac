#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
ll gcd(ll a,ll b) {
	if(b==0) return a;
	return gcd(b,a%b);
}
ll eu(ll a,ll b) {
	vector<ll> r={1,0};
	vector<ll> s={0,1};
	vector<ll> t={a,b};
	ll u=a/b;
	ll x,y,z;
	while(1) {
		y=t[t.size()-2];
		x=t[t.size()-1];
		z=y%x;
		t.push_back(z);
		if (z==0) return s[s.size()-1];
		u=y/x;
		r.push_back(r[r.size()-2]-r[r.size() - 1]*u);
		s.push_back(s[s.size() - 2]-s[s.size()-1]*u);
	}
} int main() {
	ll n,a;
	cin >> n >> a;
	cout << n-a << ' ';
	if(gcd(n,a)!=1) {
		cout << -1;
		return 0;
	} ll r=eu(n,a);
	while(r<0) {
		r+=n;
	} cout << r;
}
