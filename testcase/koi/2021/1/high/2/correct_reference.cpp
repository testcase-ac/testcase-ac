#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;
typedef tuple<ll, ll, ll> tpl;

ll n, k, a[4];
vector<ll> v[4];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 0; i < 4; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++) {
		char t1;
		ll t2;
		cin >> t1 >> t2;
		v[t1 - 'A'].push_back(t2);
	}
	
	for(int i=0;i<4;i++)
		sort(all(v[i]), greater<ll>());
	
	vector<tpl> p;
	for (int i = 0; i < 4; i++) {
		ll s = a[i];
		for (auto h : v[i]) {
			s += h;
			p.emplace_back(h, s, i);
		}
	}
	sort(all(p), [&](tpl t1, tpl t2) {
		auto [h1, s1, i1] = t1;
		auto [h2, s2, i2] = t2;
		return h1 * s2 > h2 * s1;
	});
	for (int i = 0; i < k; i++) {
		auto [h, s, idx] = p[i];
		cout << (char)('A' + idx) << ' ' << h << '\n';
	}
	return 0;
}
