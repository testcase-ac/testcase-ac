#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
ll factorial(ll i) {
	ll ret = 1;
	for(int j=2; j<=i; j++) ret *= j;
	return ret;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		ll n, t, l, k=100000000;
		cin >> n >> t >> l;
		bool tle = false;
		if(s == "O(N)") {
			tle = (n * t / k) > l;
		} else if(s == "O(2^N)") {
			tle = (n >= 40 || (1LL << n) * t > l*k);
		} else if(s == "O(N!)") {
			tle = (n >= 15 || factorial(n) * t > l*k);
		} else if(s == "O(N^2)") {
			tle = (n >= 1e7 || n*n*t > l*k);
		} else if(s == "O(N^3)") {
			tle = (n >= 1e4 || n*n*n*t > l*k);
		}
		if(tle) cout << "TLE!\n";
		else cout << "May Pass.\n";
	}
}
