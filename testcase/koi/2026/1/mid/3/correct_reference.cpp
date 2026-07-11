/*
 * Model solution code (C++)
 * Gyojun Youn
 * youn [dot] gyojun [at] gmail [dot] com
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;

const int LG = 19, MX = 1 << LG;

int P[LG][MX];

vector<int> G[MX];

struct {
	ll v;
	int a, b;
} F[MX];

ll A[MX], B[MX], D[MX];
int E[MX], U[MX], O[MX], RO[MX];

int N;

struct {
	ll v = -0x3f3f3f3f3f3f3f3fLL;
	int a, b;

	void upd(int x, int y, ll z) {
		if (x == y || z <= v) return;
		v = z; a = x; b = y;
	}

	void prt() {
		cout << a << ' ' << b << '\n';
	}
} Ans;

int uf(int x) { return x == U[x] ? x : (U[x] = uf(U[x])); }

int lca(int a, int b) {
	if (E[a] > E[b]) swap(a, b);
	int d = E[b] - E[a];
	for (int i = LG; i--;) if (d >> i & 1) b = P[i][b];
	if (a == b) return a;
	for (int i = LG; i--;)
		if (int pa = P[i][a], pb = P[i][b]; pa != pb)
			a = pa, b = pb;
	return P[0][a];
}

ll dst(int a, int b) { return D[a] + D[b] - D[lca(a, b)] * 2; }

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr);

	cin >> N;
	for (int i = 1; i <= N; i++) cin >> A[i];
	for (int i = 1; i < N; i++) cin >> P[0][i];
	for (int i = 1; i < N; i++) cin >> B[i];

	iota(U, U + N + 1, 0);
	iota(O, O + N + 1, 0);
	sort(O + 1, O + N + 1, [&](int a, int b) { return A[a] < A[b]; });
	for (int i = 1; i <= N; i++) RO[O[i]] = i;
	for (int i = N; --i;) D[i] = D[P[0][i]] + B[i];
	for (int i = N; --i;) E[i] = E[P[0][i]] + 1;
	for (int j = 1; j < LG; j++) for (int i = 1; i <= N; i++)
		P[j][i] = P[j - 1][P[j - 1][i]];
	for (int i = 1; i < N; i++) {
		int a = i, b = P[0][i];
		if (RO[a] < RO[b]) swap(a, b);
		G[a].push_back(b);
	}

	for (int oi = 1; oi <= N; oi++) {
		int p = O[oi];

		F[p].a = F[p].b = p;
		ll lpa = 0, lpb = 0;
		for (int v : G[p]) {
			int g = uf(v); U[g] = p;

			ll w = B[min(p, v)], lva = dst(v, F[g].a), lvb = dst(v, F[g].b);
			if (lva < lvb) swap(lva, lvb), swap(F[g].a, F[g].b);

			ll nv = lpa + w + lva, mx = max({F[p].v, F[g].v, nv});
			if (mx == F[p].v) continue;
			else if (mx == nv) {
				lpb = lva + w; F[p].b = F[g].a;
				if (lpa < lpb) swap(lpa, lpb), swap(F[p].a, F[p].b);
			} else F[p].a = F[g].a, F[p].b = F[g].b, lpa = lva + w, lpb = lvb + w;
			F[p].v = mx;
		}

		Ans.upd(F[p].a, F[p].b, F[p].v - A[p]);
	}

	Ans.prt();
	return 0;
}
