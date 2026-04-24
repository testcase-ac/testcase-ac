#include <bits/stdc++.h>
using namespace std;

const int MX = 200000;
struct Edge {
	int x, y, d;
	bool operator< (Edge &e) {
		return d < e.d;
	}
};
struct DSU {
	vector<int> par;
	// more variable here, like setsz
	int n;
	DSU(int a) {
		n = a;
		par.resize(n);
		for(int i=0; i<n; i++) {
			par[i] = i;
			// more init here
		}
	}
	int find(int i) {
		return i == par[i] ? i : par[i] = find(par[i]);
	}
	void join(int i, int j) {
		i = find(i), j = find(j);
		if(i != j) {
			par[j] = i;
			// more logic here
		}
	}
	bool sameset(int i, int j) {
		return find(i) == find(j);
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		int V, E;
		cin >> V >> E;
		if(!V && !E) break;
		vector<Edge> v;
		int orig = 0;
		for(int i=0; i<E; i++) {
			int x, y, z;
			cin >> x >> y >> z;
			v.push_back({x,y,z});
			orig += z;
		}
		sort(v.begin(), v.end());
		DSU dsu(V);
		int now = 0, cnt = 0;
		for(Edge &e: v) {
			if(!dsu.sameset(e.x, e.y)) {
				dsu.join(e.x, e.y);
				now += e.d;
				cnt++;
				if(cnt == V-1) {
					break;
				}
			}
		}
		cout << orig - now << '\n';
	}
}
