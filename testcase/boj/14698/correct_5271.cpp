#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		ll ans = 1;
		int n;
		cin >> n;
		priority_queue<ll, vector<ll>, greater<ll>> pq;
		while(n--) {
			ll t;
			cin >> t;
			pq.push(t);
		}
		while(pq.size() > 1) {
			ll a, b;
			a = pq.top();
			pq.pop();
			b = pq.top();
			pq.pop();
			ans = (ans * ((a * b) % MOD)) % MOD;
			pq.push(a*b);
		}
		cout << ans << '\n';
	}
}
