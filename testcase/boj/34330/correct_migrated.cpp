#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using t3 = tuple<int, int, int>;
using i128 = __int128;

struct st {
	ll x, y, r;
};

ll R, L, N, M, p[101];

ll find(ll x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}

void merge(ll x, ll y) {
	x = find(x);
	y = find(y);
	if (x == y) return;
	if (x > y) swap(x, y);
	p[x] = y;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> R >> L >> N >> M;
	vector<st> a(N), b(M);
	p[N] = N;
	for (ll i = 0; i < N; ++i) p[i] = i;
	for (ll i = 0; i < N; ++i) {
		cin >> a[i].x >> a[i].y >> a[i].r;
		if (R < a[i].r) merge(i, N);
		else if ((R - a[i].r) * (R - a[i].r) <= a[i].x * a[i].x + a[i].y * a[i].y) {
			merge(i, N);
		}
	}
	for (ll i = 0; i < N; ++i) {
		for (ll j = 0; j < N; ++j) {
			ll d = (a[i].x - a[j].x) * (a[i].x - a[j].x)
			+ (a[i].y - a[j].y) * (a[i].y - a[j].y);
			if (d <= (a[i].r + a[j].r) * (a[i].r + a[j].r)) {
				merge(i, j);
			}
		}
	}
	ll c = 0;
	for (ll i = 0; i < M; ++i) {
		cin >> b[i].x >> b[i].y;
		ll f = 0;
		for (ll j = 0; j < N; ++j) {
			if (find(j) < N) continue;
			ll d = (b[i].x - a[j].x) * (b[i].x - a[j].x)
			+ (b[i].y - a[j].y) * (b[i].y - a[j].y);
			if (d <= (L + a[j].r) * (L + a[j].r)) {
				f = 1;
				break;
			}
		}
		if (R < L) f = 1;
		else if ((R - L) * (R - L) <= b[i].x * b[i].x + b[i].y * b[i].y) f = 1;
		c += f;
	}
	cout << c;
	return 0;
}
