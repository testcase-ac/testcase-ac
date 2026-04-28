#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int n, k, sz, P[7501], E[28121250];

int Find(int x) { return P[x] < 0 ? x : P[x] = Find(P[x]); }
bool Union(int a, int b) {
	a = Find(a), b = Find(b);
	return a == b ? 0 : (P[b] = a, 1);
}

int main() {
	fastio;
	cin >> n >> k; memset(P, -1, sizeof P);
	for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) E[sz++] = i << 13 | j;
	sort(E, E + sz, [](int a, int b) {
		return 84 * (a >> 13) + 48 * (a & 8191) > 84 * (b >> 13) + 48 * (b & 8191);
	});
	for (int i = 0; i < sz; i++) {
		if (!Union(E[i] >> 13, E[i] & 8191)) continue;
		if (n-- == k) {
			cout << 2019201997 - 84 * (E[i] >> 13) - 48 * (E[i] & 8191) << '\n';
			break;
		}
	}
}
