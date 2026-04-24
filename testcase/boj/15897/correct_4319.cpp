#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
inline ll ceiling(ll p, ll q) {
	return (p % q == 0 ? p/q : p/q+1);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	ll n;
	cin >> n;
	ll sqn = sqrt(n);
	ll ans = 0, lastk = n+1;
	for(int cnt=1;cnt<=sqn; cnt++) {
		ll thisk = ceiling(n, cnt);
		ans += (cnt * (lastk-thisk));
		lastk = thisk;
	}
	for(int i=1;;i++) {
		ll cnt = ceiling(n, i);
		if(cnt <= sqn) break;
		ans += cnt;
	}
	cout << ans;
}
