/*
 * Official Solution (C++17)
 * Gyojun Youn
 * youngyojun [at] gmail [dot] com
 */
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#define eb emplace_back
#define rb(x) ((x)&(-(x)))
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
inline void die() { puts("NO"); exit(0); }

const int MAXN = 250'055;

struct SEG {
	static const int MX = 250'055;
	int d[MX];

	void init() { memset(d, 0, MX * sizeof(int)); }

	void upd(int x, int r) {
		while(x < MX) {
			if(d[x] < r) d[x] = r;
			x += rb(x);
		}
	}

	int get(int x) {
		int r = 0;
		while(x) {
			if(r < d[x]) r = d[x];
			x -= rb(x);
		}
		return r;
	}
} seg;

vector<int> G[MAXN];
priority_queue<pii, vector<pii>, greater<pii>> H;

int X[MAXN], Y[MAXN], A[MAXN], B[MAXN];
int O[MAXN];

int Ans[MAXN];

int N;

int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; i++)
		scanf("%d%d%d%d", X+i, Y+i, A+i, B+i);

	for(int i = N; i; i--) O[X[i]] = i;

	for(int oi = 1; oi <= N; oi++) {
		int i = O[oi];
		A[i] = max(A[i], seg.get(Y[i]) + 1);
		seg.upd(Y[i], A[i]);
	}

	seg.init();
	for(int oi = N; oi; oi--) {
		int i = O[oi];
		B[i] = min(B[i], N - seg.get(N+1 - Y[i]));
		seg.upd(N+1 - Y[i], N+1 - B[i]);
	}

	for(int i = N; i; i--) {
		if(A[i] > B[i]) die();
		G[A[i]].eb(i);
	}

	for(int t = 1; t <= N; t++) {
		for(int i : G[t]) H.emplace(B[i], i);
		if(H.empty()) die();
		int v = H.top().se;
		H.pop();
		if(B[v] < t) die();
		Ans[v] = t;
	}

	puts("YES");
	for(int i = 1; i <= N; i++)
		printf("%d ", Ans[i]);
	puts("");
	return 0;
}