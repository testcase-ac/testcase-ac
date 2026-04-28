#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 200007;
ll P[MAX], W[MAX], V[MAX];
unordered_map<ll, ll> dupL, dupR;

int main() {
	//freopen("in", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0);
	ll N, L, R, ans = 0;
	cin >> N >> L >> R;
	for (int i = 0; i < N; ++i) {
		int d;
		cin >> P[i] >> d >> W[i];
		if (P[i] > 0) {
			if (P[i] * d < 0) V[i] = P[i] - 1;
			else V[i] = 2 * R - P[i];
			if (dupR[V[i]]) {
				W[dupR[V[i]] - 1] += W[i];
				W[i] = 0;
			}
			else dupR[V[i]] = i + 1;
		}
		else {
			if (P[i] * d < 0) V[i] = -P[i] - 1;
			else V[i] = 2 * L + P[i];
			if (dupL[V[i]]) {
				W[dupL[V[i]] - 1] += W[i];
				W[i] = 0;
			}
			else dupL[V[i]] = i + 1;
		}
	}

	if (__gcd(L, R) == min(L, R)) {
		ll get = (L >= R ? 1 : R / L);
		map<ll, vector<ll>> pos;
		for (int i = 0; i < N; ++i) pos[V[i] % (R * 2)].push_back(W[i]);
		for (auto& [ignore, v] : pos) {
			sort(v.begin(), v.end(), greater<ll>());
			for (int i = 0; i < min(get, (ll)v.size()); ++i) ans += v[i];
		}
	}
	else {
		ll get = R;
		vector<ll> odd, even;
		for (int i = 0; i < N; ++i) (V[i] & 1 ? odd : even).push_back(W[i]);
		sort(odd.begin(), odd.end(), greater<ll>());
		sort(even.begin(), even.end(), greater<ll>());
		for (int i = 0; i < min(get, (ll)odd.size()); ++i) ans += odd[i];
		for (int i = 0; i < min(get, (ll)even.size()); ++i) ans += even[i];
	}
	cout << ans;
	return 0;
}
