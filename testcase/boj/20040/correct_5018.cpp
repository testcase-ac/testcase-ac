#include <bits/stdc++.h>
using namespace std;
int par[500000];
int f(int i) {return par[i] == i ? i : par[i] = f(par[i]);}
int32_t main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, M;
	cin >> N >> M;
	for(int i=0; i<N; i++) {
		par[i] = i;
	}
	for(int i=1; i<=M; i++) {
		int u, v;
		cin >> u >> v;
		u = f(u);
		v = f(v);
		if(u == v)
			return !(cout << i);
		par[u] = v;
	}
	cout << 0;
}
