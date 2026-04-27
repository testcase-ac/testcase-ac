/*
 * KOI 2022 Model Solution
 *
 * Gyojun Youn
 * youngyojun@gmail.com
 *
 */

#include <cstdio>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;

const int MAXN = 250'055;

vector<int> G[MAXN];

int ud[MAXN], uc[MAXN];

int P[MAXN];
int S[MAXN];
bool inS[MAXN];

int N, Q, K;

int uf(int i) {
	return i == ud[i] ? i : (ud[i] = uf(ud[i]));
}
void uf(int a, int b) {
	a = uf(a); b = uf(b);
	if(a == b) return;
	uc[a] += uc[b];
	ud[b] = a;
}

void f(int i) {
	for(int v : G[i]) if(v != P[i]) {
		P[v] = i;
		f(v);
	}
}

int main() {
	scanf("%d", &N);
	for(int i = N-1; i--;) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}

	f(1);

	iota(ud, ud+N+1, 0);
	fill_n(uc, N+1, 1);

	scanf("%d", &Q);

	while(Q--) {
		scanf("%d", &K);
		for(int i = K; i--;) {
			int v;
			scanf("%d", &v);
			S[i] = v;
			inS[v] = true;
		}

		for(int i = K; i--;) {
			int v = S[i];
			int p = P[v];
			if(inS[p]) uf(p, v);
		}

		ll r = 0;
		for(int i = K; i--;) {
			int v = S[i];
			if(uf(v) != v)
				continue;
			int n = uc[v];
			r += ll(n) * (n-1);
		}

		printf("%lld\n", r >> 1);

		for(int i = K; i--;) {
			int v = S[i];
			ud[v] = v;
			uc[v] = 1;
			inS[v] = false;
		}
	}

	return 0;
}
