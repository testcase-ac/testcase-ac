#include <bits/stdc++.h>
using namespace std;
#define int long long

struct circle {
	int x, y, r;
	void read() {
		cin >> x >> y >> r;
	}
	double dist(circle &c) {
		double t = sqrt((x-c.x)*(x-c.x) + (y-c.y)*(y-c.y)) - r - c.r;
		if(t < 0)
			return 0;
		return t;
	}
};
struct edge {
	int u, v;
	double w;
};
struct DSU {
    vector<int> par;
    int n;
    DSU(int a) {
        n = a;
        par.resize(n);
        for(int i=0; i<n; i++) {
            par[i] = i;
        }
    }
    int find(int i) {
        return i == par[i] ? i : par[i] = find(par[i]);
    }
    void join(int i, int j) {
        i = find(i), j = find(j);
        if(i != j) {
            par[j] = i;
        }
    }
    bool sameset(int i, int j) {
        return find(i) == find(j);
    }
};
double solve() {
	int w, n;
	cin >> w >> n;
	vector<circle> circles(n);
	for(int i=0; i<n; i++) {
		circles[i].read();
	}
	vector<edge> edges;
	edges.push_back({n, n+1, w});
	for(int i=0; i<n; i++) {
		edges.push_back({n, i, max(0.0, (double)circles[i].x-circles[i].r)});
		edges.push_back({n+1, i, max(0.0, (double)w-circles[i].x-circles[i].r)});
		for(int j=i+1; j<n; j++) {
			double d = circles[i].dist(circles[j]);
			edges.push_back({i, j, d});
		}
	}
	sort(edges.begin(), edges.end(), [](auto a, auto b){return a.w < b.w;});
	DSU dsu(n+2);
	for(auto &e: edges) {
		dsu.join(e.u, e.v);
		if(dsu.sameset(n, n+1))
			return e.w / 2;
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--)
		cout << fixed << setprecision(10) << solve() << '\n';
}
