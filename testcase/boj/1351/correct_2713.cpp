#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n, p, q;
map<ll, ll> mp;
ll get(ll key) {
	auto it = mp.find(key);
	if(it == mp.end()) {
		ll r = get(key/p) + get(key/q);
		mp[key] = r;
		return r;
	} else
		return it->second;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	mp[0] = 1;
	cin >> n >> p >> q;
	cout << get(n);
}
